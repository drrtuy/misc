#!/usr/bin/python

"""
SPY class for environments. Its main usage is a variable storage/retrieval container.
"""
class Environment():
    def __init__(self,names,values,parentEnv):
        """
        Takes its arguments and constructs data structure such as dict for variables    with variable name as a key, env's parent as self.parent.
        names: list of strings
        values: list of int||strings||Function obj||Environment obj
        """
        self.vars={}
        for name,value in zip(names,values):
            self.vars[name]=value
        self.parent=parentEnv
    def add(self,symb,value):
        self.vars[symb]=value
    def lookup(self,symb):
        binding=self.vars.get(symb,None)
        #print self.vars,symb,binding
        if binding or binding==0:
            return binding            
        if self.parent: return Environment.lookup(self.parent,symb)
        return None
"""
Class for Function objects. It stores function body,formal params and parent environment. 
"""
class Function():
    def __init__(self,formal,body,env):
        """
        Saves F formal args as self.formal, function body as self.body and parent environment as self.environment.
        formal: list of strings
        body: list int||strings||Function obj||Environment obj
        env: Environment object
        """
        self.formal=formal
        self.body=body
        self.environment=env

class Primitive():
    def __init__(self,func):
        self.func=func
    def __call__(self,a=None,b=None):
        if not a and not b: return self.func()
        return self.func(a,b)

globalEnv=Environment([],[],None)
globalEnv.add('+',Primitive(lambda a,b: a+b))
globalEnv.add('-',Primitive(lambda a,b: a-b))
globalEnv.add('*',Primitive(lambda a,b: a*b))
globalEnv.add('/',Primitive(lambda a,b: a/b))
globalEnv.add('=',Primitive(lambda a,b: a==b))

def str2int(intAsString):
    """
    F converts and returns its string argument into int. Returns original argument in case of a failure  
    """
    try:
        return int(intAsString)
    except ValueError:
        return intAsString

def lhsEval(lhs, env):
    if isinstance(lhs, list):
        (tag, objectExpr, name) = lhs
        return (spyEval(objectExpr, env), name)
    else:
        return (env, lhs)

def implicitSelfFix(fObj,args,selfObj):
    #print "f body",fObj.body
    #print "f self value",selfObj
    #print "args before",args
    if len(args)==0:
        args=[selfObj]
    else:
        firstArg=args[0]
        if not isinstance(firstArg,Environment):
            args.insert(0,selfObj)
    env=Environment(fObj.formal,args,fObj.environment)
    #print "args after",args
    #print "f env vars",env.vars
    return spyEval(fObj.body,Environment(fObj.formal,args,fObj.environment))

def tokenizer(spyExprList):
    """
    Takes a SPY expression as a string and returns list of lists of lists... of allowed elements. Converts numbers to integers.
    '(set a 5)' -> ['set','a',5]
    '(begin (set a 3) (set b (+ 5 10) ) (* a b))'->['begin',['set','a',3],['set','b',['+',5,10]],['*','a','b']]
    use generator, list as a queue
    use an offset to skip list elements 
    """
    r=[]
    index=0
    #spyExprList=spyString.split()
    indexOffset=0
    while(index < len(spyExprList)):
        spyExpr=spyExprList[index]
        #print"index",index
        if spyExpr[0]=='(':
            spyExprList[index]=spyExpr[1:]            
            #print "rec start",spyExprList,"index",index
            #raw_input()
            spyElems,indexOffset=tokenizer(spyExprList[index:])
            index+=indexOffset
            r.append(spyElems)
            #print "rec finished",r,"offset",indexOffset            
        elif spyExpr[-1]==')':
            if len(spyExpr)>1:
                r.append(str2int(spyExpr[:-1]))
            #print "end of expr branch",r,"offset",(indexOffset+1)
            #raw_input()
            return r,(index+1)
        else:
            r.append(str2int(spyExpr))
            indexOffset+=1
            index+=1
            #print "else branch",r,"offset",indexOffset
            #raw_input()
    return r,index

def spyEval(form, env=globalEnv):
    if isinstance(form, int):
        return form
    elif isinstance(form, str):
        #print form,env.vars
        return env.lookup(form)
    elif form[0] == 'begin':
        val = None
        for entry in form[1:]:
            val = spyEval(entry, env)
        return val
    elif form[0] == 'set':
        (tag, lhs, expr) = form
        #print form
        (targetEnv, name) = lhsEval(lhs, env)
        #print targetEnv
        targetEnv.add(name, spyEval(expr, env))
    elif form[0] == 'def':
        (tag, name, params, body) = form
        env.add(name, Function(params, body, env))
    elif form[0] == 'if':
        (tag, condition, ifBody, elseBody) = form
        if spyEval(condition, env):
            return spyEval(ifBody, env)
        else:
            return spyEval(elseBody, env)
    elif isinstance(form[0],str) and form[0] in '=+-/*':
         (tag,oper1,oper2)=form
         #print (tag,oper1,oper2)
         #print env.vars
         return globalEnv.lookup(tag)(spyEval(oper1,env),spyEval(oper2,env))
    elif form[0] == 'attr':
        (tag, objectExpr, name) = form
        objInst=spyEval(objectExpr, env)
        attr=objInst.lookup(name)
        if isinstance(attr,Function):
            #print attr.formal
            return lambda args: implicitSelfFix(attr,args,objInst)
        return attr
    elif form[0] == 'class':
        (tag, name, super, body) = form
        if super == 'None':
            super = globalEnv
        classEnv = Environment([],[],parentEnv = super)
        env.add(name, Primitive(lambda : Environment([],[],parentEnv = classEnv)))
        spyEval(body, classEnv)
    elif isinstance(form, list):
        fName=form[0]
        f = spyEval(form[0], env)
        #print f
        #print form
        #print env.vars
        if isinstance(f,Primitive) and len(form)==1: #create a class object environment 
            return f()
        elif isinstance(f,type(lambda a: 0)):            
            return f([spyEval(x, env) for x in form[1:]])
        return spyEval(f.body,Environment(f.formal,
        [spyEval(x, env) for x in form[1:]],f.environment))
    else:
        Error("Illegal expression: "+str(form))

def spy(spyExpr):
    return spyEval(tokenizer(spyExpr.split())[0][0])

def interpr():
    while(True):
        try:
            expr=raw_input("###")
            if(expr=='exit'): break            
            result=spy(expr)
            if result: print result 
        except:
            print "Fail"
            continue

if __name__=="__main__":
    pass
    interpr()
