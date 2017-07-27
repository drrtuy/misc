CREATE ROLE sched LOGIN PASSWORD 'sched';

CREATE DATABASE devops;

\c devops

CREATE SCHEMA sched;
GRANT USAGE ON  SCHEMA sched TO sched;

--CREATE TABLE sched.queries (id bigserial PRIMARY; task jsonb);
CREATE table sched.queries(id bigserial PRIMARY KEY, updated_at timestamptz, query text, host text, task jsonb, priority int DEFAULT 100);
GRANT ALL on sched.queries TO sched;
GRANT USAGE ON sched.queries_id_seq TO sched;
