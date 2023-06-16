#ifndef STYIO_AST_H_
#define STYIO_AST_H_

/*
StyioAST
*/
class StyioAST {
  public:
    virtual ~StyioAST() {}

    virtual std::string toString(int indent = 0) = 0;

    virtual std::string toStringInline(int indent = 0) = 0;
};

/*
NoneAST: None / Null / Nil
*/
class NoneAST : public StyioAST {

  public:
    NoneAST () {}

    std::string toString(int indent = 0) {
      return std::string("None { }");
    }

    std::string toStringInline(int indent = 0) {
      return std::string("None { }");
    }
};

/*
IdAST: Identifier
*/
class IdAST : public StyioAST {
  std::string Id;

  public:
    IdAST(const std::string &id) : Id(id) {}

    std::string toString(int indent = 0) {
      return std::string("ID { ") + Id + " }";
    }

    std::string toStringInline(int indent = 0) {
      return "<ID: " + Id + ">";
    }
};

/*
IntAST: Integer
*/
class IntAST : public StyioAST {
  int Value;

  public:
    IntAST(int val) : Value(val) {}

    std::string toString(int indent = 0) {
      return "Int { " + std::to_string(Value) + " }";
    }

    std::string toStringInline(int indent = 0) {
      return std::to_string(Value);
    }
};

/*
FloatAST: Float
*/
class FloatAST : public StyioAST {
  double Value;

  public:
    FloatAST(double val) : Value(val) {}

    std::string toString(int indent = 0) {
      return "Float { " + std::to_string(Value) + " }";
    }

    std::string toStringInline(int indent = 0) {
      return std::to_string(Value);
    }
};

/*
StringAST: String
*/
class StringAST : public StyioAST {
  std::string Value;

  public:
    StringAST(std::string val) : Value(val) {}

    std::string toString(int indent = 0) {
      return "String { \"" + Value + "\" }";
    }

    std::string toStringInline(int indent = 0) {
      return "<String: \"" + Value + "\">";
    }
};

/*
PathAST: (File) Path
*/
class PathAST : public StyioAST {
  std::string Path;

  public:
    PathAST (std::string path): Path(path) {}

    std::string toString(int indent = 0) {
      return std::string("Path(File) { ") + Path + " }";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Path(File) { ") + Path + " }";
    }
};

/*
LinkAST: (Web) Link
*/
class LinkAST : public StyioAST {
  std::string Link;

  public:
    LinkAST (std::string link): Link(link) {}

    std::string toString(int indent = 0) {
      return std::string("Link(Web) { }");
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Link(Web) { }");
    }
};

/*
EmptyListAST: Empty List
*/
class EmptyListAST : public StyioAST {
  public:
    EmptyListAST() {}

    std::string toString(int indent = 0) {
      return std::string("List(Empty) [ ]");
    }

    std::string toStringInline(int indent = 0) {
      return std::string("List(Empty) [ ]");
    }
};

/*
ListAST
*/
class ListAST : public StyioAST {
  std::vector<StyioAST*> Elems;

  public:
    ListAST(std::vector<StyioAST*> elems): Elems(elems) {}

    std::string toString(int indent = 0) {
      std::string ElemStr;

      for(int i=0; i < Elems.size(); i++) {
        ElemStr += std::string(2, ' ') + "| ";
        ElemStr += Elems[i] -> toString(indent);
        ElemStr += "\n";
      };

      return std::string("List [\n")
        + ElemStr
        + "]";
    }

    std::string toStringInline(int indent = 0) {
      std::string ElemStr;

      for(int i = 0; i < Elems.size(); i++) {
        ElemStr += Elems[i] -> toStringInline(indent);
        ElemStr += ", ";
      };

      return std::string("List [ ")
        + ElemStr
        + "]";
    }
};

/*
AssignAST
*/
class AssignAST : public StyioAST {
  IdAST* varId;
  StyioAST* valExpr;

  public:
    AssignAST(IdAST* var, StyioAST* val) : varId(var), valExpr(val) {}

    std::string toString(int indent = 0) {
      return std::string("Assign (Mutable) {\n") 
        + std::string(2, ' ') + "| Var: " 
        + varId -> toString(indent) 
        + "\n"
        + std::string(2, ' ') + "| Val: " 
        + valExpr -> toStringInline(indent) 
        + "\n"
        + "}";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Assign (Mutable) {\n") 
        + std::string(2, ' ') + "| Var: " 
        + varId -> toString(indent) 
        + "; "
        + std::string(2, ' ') + "| Val: " 
        + valExpr -> toStringInline(indent) 
        + " }";
    }
};

/*
AssignFinalAST
*/
class AssignFinalAST : public StyioAST {
  IdAST* varId;
  StyioAST* valExpr;

  public:
    AssignFinalAST(IdAST* var, StyioAST* val) : varId(var), valExpr(val) {}

    std::string toString(int indent = 0) {
      return std::string("Assign (Final) {\n") 
        + std::string(2, ' ') + "| Var: " 
        + varId -> toString(indent) 
        + "\n"
        + std::string(2, ' ') + "| Val: " 
        + valExpr -> toString(indent) 
        + "\n"
        + "}";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Assign (Final) { ") 
        + std::string(2, ' ') + "| Var: " 
        + varId -> toString(indent) 
        + "; "
        + std::string(2, ' ') + "| Val: " 
        + valExpr -> toString(indent) 
        + " }";
    }
};

/*
ReadAST: Read (File)
*/
class ReadAST : public StyioAST {
  IdAST* varId;
  StyioAST* valExpr;

  public:
    ReadAST(IdAST* var, StyioAST* val) : varId(var), valExpr(val) {}

    std::string toString(int indent = 0) {
      return std::string("Read {\n") 
        + std::string(2, ' ') + "| Var: " 
        + varId -> toString(indent) 
        + "\n"
        + std::string(2, ' ') + "| Val: " 
        + valExpr -> toStringInline(indent) 
        + "\n"
        + "}";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Assign (Mutable) {\n") 
        + std::string(2, ' ') + "| Var: " 
        + varId -> toString(indent) 
        + "; "
        + std::string(2, ' ') + "| Val: " 
        + valExpr -> toStringInline(indent) 
        + " }";
    }
};

/*
BinOpAST
*/
class BinOpAST : public StyioAST {
  StyioToken Op;
  StyioAST *LHS;
  StyioAST *RHS;

  public:
    BinOpAST(StyioToken op, StyioAST* lhs, StyioAST* rhs): Op(op), LHS(lhs), RHS(rhs) {}

    std::string toString(int indent = 0) {
      return std::string("BinOp {\n") 
        + std::string(2, ' ') + "| LHS: "
        + LHS -> toString(indent) 
        + "\n"
        + std::string(2, ' ') + "| Op:  "
        + reprToken(Op)
        + "\n"
        + std::string(2, ' ') + "| RHS: "
        + RHS -> toString(indent)  
        + "\n} ";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("BinOp { ") 
        + std::string(2, ' ') + "| LHS: "
        + LHS -> toString(indent) 
        + "; "
        + std::string(2, ' ') + "| Op:  "
        + reprToken(Op)
        + "; "
        + std::string(2, ' ') + "| RHS: "
        + RHS -> toString(indent)  
        + " } ";
    }
};

/*
VarDefAST
*/
class VarDefAST : public StyioAST {
  std::vector<IdAST*> Vars;

  public:
    VarDefAST(std::vector<IdAST*> vars): Vars(vars) {}

    std::string toString(int indent = 0) {
      std::string varStr;

      for (std::vector<IdAST*>::iterator it = Vars.begin(); 
        it != Vars.end(); 
        ++it
      ) {
        varStr += std::string(2, ' ') + "| ";
        varStr += (*it) -> toStringInline();
        varStr += "\n";
      };

      return std::string("Variable Definition {\n")
        + varStr
        + "} ";
    }

    std::string toStringInline(int indent = 0) {
      std::string varStr;

      for (std::vector<IdAST*>::iterator it = Vars.begin(); 
        it != Vars.end(); 
        ++it
      ) {
        varStr += std::string(2, ' ') + "| ";
        varStr += (*it) -> toStringInline();
        varStr += " ;";
      };

      return std::string("Var Def { ")
        + varStr
        + " } ";
    }
};

/*
BlockAST: Block
*/
class BlockAST : public StyioAST {
  std::vector<StyioAST*> Stmts;
  StyioAST* Expr;

  public:
    BlockAST() {}

    BlockAST(StyioAST* expr): Expr(expr) {}

    BlockAST(std::vector<StyioAST*> stmts, StyioAST* expr): Stmts(stmts), Expr(expr) {}

    std::string toString(int indent = 0) {
      std::string stmtStr;

      for (std::vector<StyioAST*>::iterator it = Stmts.begin(); 
        it != Stmts.end(); 
        ++it
      ) {
        stmtStr += (*it) -> toStringInline();
        stmtStr += "\n";
      };

      return std::string("Block {\n")
        + std::string(2, ' ') + "| Stmts: "
        + stmtStr
        + "\n"
        + std::string(2, ' ') + "| Expr:  "
        + Expr -> toString()  
        + "\n} ";
    }

    std::string toStringInline(int indent = 0) {
      std::string stmtStr;

      for (std::vector<StyioAST*>::iterator it = Stmts.begin(); 
        it != Stmts.end(); 
        ++it
      ) {
        stmtStr += (*it) -> toStringInline();
        stmtStr += " ;";
      };

      return std::string("Block { ")
        + std::string(2, ' ') + "| Stmts: "
        + stmtStr
        + " |"
        + std::string(2, ' ') + "| Expr:  "
        + Expr -> toString()  
        + " } ";
    }
};

/*
ExtPacAST: External Packages
*/
class ExtPacAST : public StyioAST {
  std::vector<std::string> PacPaths;

  public:
    ExtPacAST(std::vector<std::string> paths): PacPaths(paths) {}

    std::string toString(int indent = 0) {
      std::string pacPathStr;

      for(int i = 0; i < PacPaths.size(); i++) {
        pacPathStr += std::string(2, ' ') + "| ";
        pacPathStr += PacPaths[i];
        pacPathStr += "\n";
      };

      return std::string("Ext Pac {\n")
        + pacPathStr
        + "\n} ";
    }

    std::string toStringInline(int indent = 0) {
      std::string pacPathStr;

      for(int i = 0; i < PacPaths.size(); i++) {
        pacPathStr += std::string(2, ' ') + "| ";
        pacPathStr += PacPaths[i];
        pacPathStr += " ;";
      };

      return std::string("Dependencies { ")
        + pacPathStr
        + " } ";
    }
};

/*
StdOutAST: Standard Output
*/
class StdOutAST : public StyioAST {
  StringAST* Output;

  public:
    StdOutAST(StringAST* output): Output(output) {}

    std::string toString(int indent = 0) {
      return std::string("stdout {\n")
        + std::string(2, ' ') + "| "
        + Output -> toString()
        + "\n}";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("stdout { ")
        + std::string(2, ' ') + "| "
        + Output -> toString()
        + " }";
    }
};

/*
InfiniteAST: Infinite Loop
  incEl Increment Element
*/
class InfiniteAST : public StyioAST {
  IdAST* IncEl;

  public:
    InfiniteAST() {}

    std::string toString(int indent = 0) {
      return std::string("Infinite { }");
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Infinite { }");
    }
};

/*
LoopAST: Loop
*/
class LoopAST : public StyioAST {
  StyioAST* Start;
  StyioAST* End;
  StyioAST* Step;
  BlockAST* Block;

  public:
    LoopAST(IntAST* start, IntAST* step, BlockAST* block): Start(start), Step(step), Block(block) {}

    std::string toString(int indent = 0) {
      return std::string("Loop {\n")
        + std::string(2, ' ') + "| Start: " + Start -> toString() + "\n"
        + std::string(2, ' ') + "| End: " + End -> toString() + "\n"
        + std::string(2, ' ') + "| Step: " + Step -> toString() + "\n"
        + std::string(2, ' ') + "| Block: " + Block -> toString() + "\n"
        + "\n}";
    }
};

#endif