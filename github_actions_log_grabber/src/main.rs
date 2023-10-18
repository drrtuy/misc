use std::io::Read;

use bytes::Bytes;
use octocrab::Octocrab;
use tokio::fs::File;
use tokio::{io::AsyncWriteExt, task};
use zip::ZipArchive;

async fn write_to_file(bytes: Bytes, path: &str) -> tokio::io::Result<()> {
    let mut file = File::create(path).await?;
    file.write_all(&bytes).await?;
    Ok(())
}

async fn search_for_pattern(path: String) -> Result<(), Box<dyn std::error::Error>> {
    use std::fs::File;

    let _: Result<_, std::io::Error> = task::spawn_blocking(move || {
        let file = File::open(path.clone())?;
        println!("path: {path}");
        let mut archive: ZipArchive<File> = ZipArchive::new(file)?;
        let mut file_in_archive = archive.by_name("nox  cargo nextest/9_Run cargo nextest.txt")?;

        let mut contents = String::new();

        file_in_archive.read_to_string(&mut contents)?;
        if contents.contains("fold_fold_fold_seq_two_par_null_folds") {
            println!("!!! the pattern matching in {path}");
        }
        Ok(())
    })
    .await?;

    Ok(())
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let token = std::env::var("GITHUB_TOKEN").expect("GITHUB_TOKEN env var is required");
    let owner = "fluencelabs";
    let repo = "nox";
    let workflow_id = "35813939"; // AKA test
    let workflow_name = "test";
    let store_path = "/git/fluence-run-logs/";

    let octo = Octocrab::builder().personal_token(token).build()?;

    let mut page_num: u32 = 1;
    loop {
        let page = octo
            .workflows(owner, repo)
            .list_runs(workflow_id)
            .status("failure")
            .page(page_num)
            .per_page(100)
            .send()
            .await?;

        let next_page_available = page.next.is_none();

        for run in page.into_iter().filter(|run| run.name == workflow_name) {
            let run_id = run.id;
            print!("Run id {run_id}\t",);
            let archive_as_bytes = octo
                .actions()
                .download_workflow_run_logs(owner, repo, run_id)
                .await?;
            let path = format!("{store_path}{repo}-{workflow_id}-{run_id}.zip");
            write_to_file(archive_as_bytes, &path).await?;
            search_for_pattern(path).await?;
        }

        if next_page_available {
            break;
        }

        page_num += 1;
        println!("Page {page_num}");
    }

    Ok(())
}
