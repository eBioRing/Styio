#ifndef STYIO_AST_H_
#define STYIO_AST_H_

/*
  StyioAST
*/
class StyioAST {
  public:
    virtual ~StyioAST() {}

    virtual StyioType hint() = 0;

    virtual std::string toString(int indent = 0) = 0;

    virtual std::string toStringInline(int indent = 0) = 0;
};

/*
  =================
    None / Empty
  =================
*/

/*
  NoneAST: None / Null / Nil
*/
class NoneAST : public StyioAST {

  public:
    NoneAST () {}

    StyioType hint() {
      return StyioType::None;
    }

    std::string toString(int indent = 0) {
      return std::string("None { }");
    }

    std::string toStringInline(int indent = 0) {
      return std::string("None { }");
    }
};

/*
  EmptyListAST: Empty List
*/
class EmptyListAST : public StyioAST {
  public:
    EmptyListAST() {}

    StyioType hint() {
      return StyioType::EmptyList;
    }

    std::string toString(int indent = 0) {
      return std::string("List(Empty) [ ]");
    }

    std::string toStringInline(int indent = 0) {
      return std::string("List(Empty) [ ]");
    }
};

/*
  EmptyBlockAST: Block
*/
class EmptyBlockAST : public StyioAST {
  public:
    EmptyBlockAST() {}

    StyioType hint() {
      return StyioType::EmptyBlock;
    }

    std::string toString(int indent = 0) {
      return std::string("Block (Empty) { ")
        + " } ";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Block (Empty) { ")
        + " } ";
    }
};

/*
  =================
    Variable
  =================
*/

/*
  IdAST: Identifier
*/
class IdAST : public StyioAST {
  std::string Id;

  public:
    IdAST(const std::string &id) : Id(id) {}

    StyioType hint() {
      return StyioType::Id;
    }

    std::string toString(int indent = 0) {
      return std::string("ID { ") + Id + " }";
    }

    std::string toStringInline(int indent = 0) {
      return "<ID: " + Id + ">";
    }
};

/*
  =================
    Scalar Value
  =================
*/

/*
  IntAST: Integer
*/
class IntAST : public StyioAST {
  int Value;

  public:
    IntAST(int val) : Value(val) {}

    StyioType hint() {
      return StyioType::Int;
    }

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

    StyioType hint() {
      return StyioType::Float;
    }

    std::string toString(int indent = 0) {
      return "Float { " + std::to_string(Value) + " }";
    }

    std::string toStringInline(int indent = 0) {
      return std::to_string(Value);
    }
};

/*
  CharAST: Character
*/
class CharAST : public StyioAST {
  std::string Value;

  public:
    CharAST(std::string val) : Value(val) {}

    StyioType hint() {
      return StyioType::Char;
    }

    std::string toString(int indent = 0) {
      return "Character { \"" + Value + "\" }";
    }

    std::string toStringInline(int indent = 0) {
      return "<Character: \"" + Value + "\">";
    }
};

/*
  =================
    Data Resource Identifier
  =================
*/

/*
  ExtPathAST: (File) Path
*/
class ExtPathAST : public StyioAST {
  std::string Path;

  public:
    ExtPathAST (std::string path): Path(path) {}

    StyioType hint() {
      return StyioType::ExtPath;
    }

    std::string toString(int indent = 0) {
      return std::string("Path(File) { ") + Path + " }";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Path(File) { ") + Path + " }";
    }
};

/*
  ExtLinkAST: (Web) Link
*/
class ExtLinkAST : public StyioAST {
  std::string Link;

  public:
    ExtLinkAST (std::string link): Link(link) {}

    StyioType hint() {
      return StyioType::ExtLink;
    }

    std::string toString(int indent = 0) {
      return std::string("Link(Web) { }");
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Link(Web) { }");
    }
};

/*
  =================
    Collection
  =================
*/

/*
  StringAST: String
*/
class StringAST : public StyioAST {
  std::string Value;

  public:
    StringAST(std::string val) : Value(val) {}

    StyioType hint() {
      return StyioType::String;
    }

    std::string toString(int indent = 0) {
      return "String { \"" + Value + "\" }";
    }

    std::string toStringInline(int indent = 0) {
      return "<String: \"" + Value + "\">";
    }
};

/*
  ListAST: List (Extendable)
*/
class ListAST : public StyioAST {
  std::vector<StyioAST*> Elems;

  public:
    ListAST(std::vector<StyioAST*> elems): Elems(elems) {}

    StyioType hint() {
      return StyioType::List;
    }

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
  RangeAST: Loop
*/
class RangeAST : public StyioAST {
  StyioAST* StartVal;
  StyioAST* EndVal;
  StyioAST* StepVal;

  public:
    RangeAST(StyioAST* start, StyioAST* end, StyioAST* step): StartVal(start), EndVal(end), StepVal(step) {}

    StyioType hint() {
      return StyioType::Range;
    }

    std::string toString(int indent = 0) {
      return std::string("Collection.Range {\n")
        + std::string(2, ' ') + "| Start: " + StartVal -> toString() + "\n"
        + std::string(2, ' ') + "| End: " + EndVal -> toString() + "\n"
        + std::string(2, ' ') + "| Step: " + StepVal -> toString() + "\n"
        + "\n}";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Collection.Range {\n")
        + std::string(2, ' ') + "| Start: " + StartVal -> toString() + "\n"
        + std::string(2, ' ') + "| End: " + EndVal -> toString() + "\n"
        + std::string(2, ' ') + "| Step: " + StepVal -> toString() + "\n"
        + "\n}";
    }
};

/*
  =================
    Basic Operation
  =================
*/

/*
  SizeOfAST: Get Size(Length) Of A Collection
*/
class SizeOfAST : public StyioAST {
  StyioAST* Value;

  public:
    SizeOfAST(StyioAST* value): Value(value) {}

    StyioType hint() {
      return StyioType::SizeOf;
    }

    std::string toString(int indent = 0) {
      return std::string("SizeOf { ") 
      + Value -> toString()
      + " }";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("SizeOf { ") 
      + Value -> toStringInline()
      + " }";
    }
};

/*
  BinOpAST: Binary Operation

  | Variable
  | Scalar Value
    - Int
      {
        // General Operation
        Int (+, -, *, **, /, %) Int => Int
        
        // Bitwise Operation
        Int (&, |, >>, <<, ^) Int => Int
      }
    - Float
      {
        // General Operation
        Float (+, -, *, **, /, %) Int => Float
        Float (+, -, *, **, /, %) Float => Float
      }
    - Char
      {
        // Only Support Concatenation
        Char + Char => String
      }
  | Collection
    - Empty
      | Empty Tuple
      | Empty List (Extendable)
    - Tuple <Any>
      {
        // Only Support Concatenation
        Tuple<Any> + Tuple<Any> => Tuple
      }
    - Array <Scalar Value> // Immutable, Fixed Length
      {
        // (Only Same Length) Elementwise Operation
        Array<Any>[Length] (+, -, *, **, /, %) Array<Any>[Length] => Array<Any>

        // General Operation
        Array<Int> (+, -, *, **, /, %) Int => Array<Int>
        Array<Float> (+, -, *, **, /, %) Int => Array<Float>

        Array<Int> (+, -, *, **, /, %) Float => Array<Float>
        Array<Float> (+, -, *, **, /, %) Float => Array<Float>
      }
    - List
      {
        // Only Support Concatenation
        List<Any> + List<Any> => List<Any>
      }
    - String
      {
        // Only Support Concatenation
        String + String => String
      }
  | Blcok (With Return Value)
*/
class BinOpAST : public StyioAST {
  BinOpType Op;
  StyioAST *LHS;
  StyioAST *RHS;

  public:
    BinOpAST(BinOpType op, StyioAST* lhs, StyioAST* rhs): Op(op), LHS(lhs), RHS(rhs) {}

    StyioType hint() {
      return StyioType::BinOp;
    }

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
      return std::string("BinOp {") 
        + " LHS: "
        + LHS -> toStringInline(indent) 
        + " | Op: "
        + reprToken(Op)
        + " | RHS: "
        + RHS -> toStringInline(indent)  
        + " }";
    }
};

/*

*/
class ListOpAST : public StyioAST {
  StyioAST* TheList;
  ListOpType OpType;

  IntAST* Index;
  StyioAST* Value;

  std::vector<IntAST*> IndexList;
  std::vector<StyioAST*> ValueList;

  public:
    /*
      Get_Index_By_Item
        [?= value]

      Remove_Item_By_Value
        [-: ?= value]

      Get_Index_By_Item_From_Right
        [[<] ?= value]

      Remove_Item_By_Value_From_Right
        [[<] -: ?= value]
    */
    ListOpAST(
      StyioAST* theList, 
      ListOpType opType, 
      StyioAST* item): 
      TheList(theList), 
      OpType(opType), 
      Value(item) {}

    /*
      Insert_Item_By_Index
        [+: index <- value]
    */
    ListOpAST(
      StyioAST* theList, 
      ListOpType opType, 
      IntAST* index, 
      StyioAST* item): 
      TheList(theList), 
      OpType(opType), 
      Index(index), 
      Value(item) {}

    /*
      Remove_Item_By_Index
        [-: index] 
    */
    ListOpAST(
      StyioAST* theList, 
      ListOpType opType, 
      IntAST* index): 
      TheList(theList), 
      OpType(opType), 
      Index(index) {}

    /*
      Remove_Many_Items_By_Indices
        [-: (i0, i1, ...)]
    */
    ListOpAST(
      StyioAST* theList, 
      ListOpType opType, 
      std::vector<IntAST*> indexList): 
      TheList(theList), 
      OpType(opType), 
      IndexList(indexList) {}

    /*
      Remove_Many_Items_By_Values
        [-: ?^ (v0, v1, ...)]

      Remove_Many_Items_By_Values_From_Right
        [[<] -: ?^ (v0, v1, ...)]
    */
    ListOpAST(
      StyioAST* theList, 
      ListOpType opType, 
      std::vector<StyioAST*> valueList): 
      TheList(theList), 
      OpType(opType), 
      ValueList(valueList) {}

    /*
      Get_Reversed
        [<]
    */
    ListOpAST(
      StyioAST* theList, 
      ListOpType opType
      ): 
      TheList(theList), 
      OpType(opType) {}

    StyioType hint() {
      return StyioType::ListOp;
    }

    std::string toString(int indent = 0) {
      return std::string("List[Operation] { \n") 
      + std::string(2, ' ') + "Type { " + reprListOp(OpType) + " }\n"
      + std::string(2, ' ') + TheList -> toString() + "\n"
      + "}";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("List[Operation] { ") 
      + reprListOp(OpType) 
      + TheList -> toStringInline()
      + " }";
    }
};

/*
  =================
    Statement: Variable Definition
  =================
*/

/*
  VarDefAST: Variable Definition

  Definition = 
    Declaration (Neccessary)
    + | Assignment (Optional)
      | Import (Optional)
*/
class VarDefAST : public StyioAST {
  std::vector<IdAST*> Vars;

  public:
    VarDefAST(std::vector<IdAST*> vars): Vars(vars) {}

    StyioType hint() {
      return StyioType::VarDef;
    }

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
  =================
    Statement: Variable Assignment (Variable-Value Binding)
  =================
*/

/*
  FlexBindAST: Mutable Assignment (Flexible Binding)
*/
class FlexBindAST : public StyioAST {
  IdAST* varId;
  StyioAST* valExpr;

  public:
    FlexBindAST(IdAST* var, StyioAST* val) : varId(var), valExpr(val) {}

    StyioType hint() {
      return StyioType::MutAssign;
    }

    std::string toString(int indent = 0) {
      return std::string("Assign (Mutable) {\n") 
        + std::string(2, ' ') + "| Var: " 
        + varId -> toString(indent) 
        + "\n"
        + std::string(2, ' ') + "| Val: " 
        + valExpr -> toString(indent) 
        + "\n"
        + "}";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Assign (Mutable) {\n") 
        + std::string(2, ' ') + "| Var: " 
        + varId -> toStringInline(indent) 
        + "; "
        + std::string(2, ' ') + "| Val: " 
        + valExpr -> toStringInline(indent) 
        + " }";
    }
};

/*
  FinalBindAST: Immutable Assignment (Final Binding)
*/
class FinalBindAST : public StyioAST {
  IdAST* varId;
  StyioAST* valExpr;

  public:
    FinalBindAST(IdAST* var, StyioAST* val) : varId(var), valExpr(val) {}

    StyioType hint() {
      return StyioType::FixAssign;
    }

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
  =================
    OS Utility: IO Stream
  =================
*/

/*
  ReadFileAST: Read (File)
*/
class ReadFileAST : public StyioAST {
  IdAST* varId;
  StyioAST* valExpr;

  public:
    ReadFileAST(IdAST* var, StyioAST* val) : varId(var), valExpr(val) {}

    StyioType hint() {
      return StyioType::ReadFile;
    }

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
      return std::string("Read {\n") 
        + std::string(2, ' ') + "| Var: " 
        + varId -> toString(indent) 
        + "; "
        + std::string(2, ' ') + "| Val: " 
        + valExpr -> toStringInline(indent) 
        + " }";
    }
};

/*
  WriteStdOutAST: Write to Standard Output (Print)
*/
class WriteStdOutAST : public StyioAST {
  StringAST* Output;

  public:
    WriteStdOutAST(StringAST* output): Output(output) {}

    StyioType hint() {
      return StyioType::WriteStdOut;
    }

    std::string toString(int indent = 0) {
      return std::string("Write (StdOut) {\n")
        + std::string(2, ' ') + "| "
        + Output -> toString()
        + "\n}";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Write (StdOut) { ")
        + std::string(2, ' ') + "| "
        + Output -> toString()
        + " }";
    }
};

/*
  =================
    Abstract Level: Dependencies
  =================
*/

/*
  ExtPackAST: External Packages
*/
class ExtPackAST : public StyioAST {
  std::vector<std::string> PackPaths;

  public:
    ExtPackAST(std::vector<std::string> paths): PackPaths(paths) {}

    StyioType hint() {
      return StyioType::ExtPack;
    }

    std::string toString(int indent = 0) {
      std::string pacPathStr;

      for(int i = 0; i < PackPaths.size(); i++) {
        pacPathStr += std::string(2, ' ') + "| ";
        pacPathStr += PackPaths[i];
        pacPathStr += "\n";
      };

      return std::string("External Packages {\n")
        + pacPathStr
        + "\n} ";
    }

    std::string toStringInline(int indent = 0) {
      std::string pacPathStr;

      for(int i = 0; i < PackPaths.size(); i++) {
        pacPathStr += std::string(2, ' ') + "| ";
        pacPathStr += PackPaths[i];
        pacPathStr += " ;";
      };

      return std::string("External Packages { ")
        + pacPathStr
        + " } ";
    }
};

/*
  =================
    Abstract Level: Block 
  =================
*/

/*
  BlockAST: Block
*/
class BlockAST : public StyioAST {
  std::vector<StyioAST*> Stmts;
  StyioAST* RetExpr;

  public:
    BlockAST() {}

    BlockAST(
      StyioAST* expr): 
      RetExpr(expr) 
      {

      }

    BlockAST(
      std::vector<StyioAST*> stmts): 
      Stmts(stmts) 
      {

      }

    BlockAST(
      std::vector<StyioAST*> stmts, 
      StyioAST* expr): 
      Stmts(stmts), 
      RetExpr(expr) 
      {

      }

    StyioType hint() {
      return StyioType::Block;
    }

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
        + std::string(2, ' ') + "| RetExpr:  "
        + RetExpr -> toString()  
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
        + std::string(2, ' ') + "| Statements: "
        + stmtStr
        + " |"
        + std::string(2, ' ') + "| Expressions:  "
        + RetExpr -> toString()  
        + " } ";
    }
};

/*
  MatchBlockAST: Match Block (Cases)
*/
class MatchBlockAST : public StyioAST {
  std::vector<std::tuple<StyioAST*, StyioAST*>> Cases;

  public:
    MatchBlockAST() {}

    MatchBlockAST(
      std::vector<std::tuple<StyioAST*, StyioAST*>> cases): 
      Cases(cases) 
      {

      }

    StyioType hint() {
      return StyioType::MatchBlock;
    }

    std::string toString(int indent = 0) {
      std::string stmtStr;

      for (auto [X, Y] : Cases)
      {
        stmtStr += X -> toStringInline();
        stmtStr += Y -> toStringInline();
        stmtStr += "\n";
      };

      return std::string("Match Block (Cases) {\n")
        + std::string(2, ' ') + "| Cases: "
        + stmtStr
        + "\n"
        + "\n} ";
    }

    std::string toStringInline(int indent = 0) {
      std::string stmtStr;

      for (auto [X, Y] : Cases)
      {
        stmtStr += X -> toStringInline();
        stmtStr += Y -> toStringInline();
        stmtStr += "\n";
      };

      return std::string("Block { ")
        + std::string(2, ' ') + "| Cases: "
        + stmtStr
        + " } ";
    }
};

/*
  =================
    Abstract Level: Layers
  =================
*/

/*
  ICBSLayerAST: Intermediate Connection Between Scopes

  ExtraMatchOne:
    >> Element(Single) ?= ValueExpr(Single) => {
      ...
    }
    
    For each step of iteration, check if the element match the value expression, 
    if match case is true, then execute the branch. 

  ExtraMatchMany:
    >> Element(Single) ?= {
      v0 => {}
      v1 => {}
      _  => {}
    }
    
    For each step of iteration, check if the element match any value expression, 
    if match case is true, then execute the branch. 

  ExtraCheckIsin:
    >> Element(Single) ?^ IterableExpr(Collection) => {
      ...
    }

    For each step of iteration, check if the element is in the following collection,
    if match case is true, then execute the branch. 

  ExtraFilter: 
    >> Elements ?? (Condition) :) {
      ...
    }
    
    For each step of iteration, check the given condition, 
    if condition is true, then execute the branch. 

    >> Elements ?? (Condition) :( {
      ...
    }
    
    For each step of iteration, check the given condition, 
    if condition is false, then execute the branch. 

  Rules:
    1. If: a variable NOT not exists in its outer scope
       Then: create a variable and refresh it for each step

    2. If: a value expression can be evaluated with respect to its outer scope
       And: the value expression changes along with the iteration
       Then: refresh the value expression for each step

  How to parse ICBSLayer (for each element):
    1. Is this a [variable] or a [value expression]?
       
      Variable => 2
      Value Expression => 3

      (Hint: A value expression is something can be evaluated to a value
      after performing a series operations.)

    2. Is this variable previously defined or declared?

      Yes => 4
      No => 5

    3. Is this value expression using any variable that was NOT previously defined?

      Yes => 6
      No => 7

    4. Is this variable still mutable?

      Yes => 8
      No => 9

    5. Great! This element is a [temporary variable]
      that can ONLY be used in the following block.
      
      For each step of the iteration, you should:
        - Refresh this temporary variable before the start of the block.

    6. Error! Why is it using something that does NOT exists?
      This is an illegal value expression, 
      you should throw an exception for this.

    7. Great! This element is a [changing value expression]
      that the value is changing while iteration.

      For each step of the iteration, you should:
        - Evaluate the value expression before the start of the block.

    8. Great! This element is a [changing variable]
      that the value of thisvariable is changing while iteration.

      (Note: The value of this variable should be changed by
        some statements inside the following code block.
        However, if you can NOT find such statements,
        do nothing.)

      For each step of the iteration, you should:
        - Refresh this variable before the start of the block.

    9. Error! Why are you trying to update a value that can NOT be changed?
      There must be something wrong, 
      you should throw an exception for this.
*/

class ICBSLayerAST : public StyioAST {
  std::vector<StyioAST*> TmpVars;
  StyioAST* ExtraFilter;
  StyioAST* ExtraMatch;

  public:
    ICBSLayerAST() {}

    ICBSLayerAST(
      std::vector<StyioAST*> vars): 
      TmpVars(vars)
      {

      }

    StyioType hint() {
      return StyioType::ICBSLayer;
    }

    std::string toString(int indent = 0) {
      return std::string("Layer (Intermediate Connection Between Scopes) { }");
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Layer (Intermediate Connection Between Scopes) { }");
    }
};

/*
  =================
    Infinite loop 
  =================
*/

/*
InfLoop: Infinite Loop
  incEl Increment Element
*/
class InfLoopAST : public StyioAST {
  StyioAST* Start;
  StyioAST* IncEl;

  public:
    InfLoopAST() {}

    InfLoopAST(StyioAST* start, StyioAST* incEl): Start(start), IncEl(incEl) {}

    StyioType hint() {
      return StyioType::InfLoop;
    }

    std::string toString(int indent = 0) {
      return std::string("InfLoop { }");
    }

    std::string toStringInline(int indent = 0) {
      return std::string("InfLoop { }");
    }
};

/*
  =================
    Iterator
  =================
*/

/*
  IterInfLoopAST: [...] >> {}
*/
class IterInfLoopAST : public StyioAST {
  std::vector<IdAST*> TmpVars;
  StyioAST* TheBlock;

  public:
    IterInfLoopAST(
      StyioAST* block):
      TheBlock(block)
      {

      }

    IterInfLoopAST(
      std::vector<IdAST*> tmpVars,
      StyioAST* block):
      TmpVars(tmpVars),
      TheBlock(block)
      {

      }

    StyioType hint() {
      return StyioType::IterInfLoop;
    }

    std::string toString(int indent = 0) {
      return std::string("Iter (InfLoop) { ") 
      + " }";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Iter (InfLoop) { ")
      + " }";
    }
};

/*
  IterListAST: <List> >> {}
*/
class IterListAST : public StyioAST {
  StyioAST* TheList;
  std::vector<IdAST*> TmpVars;
  StyioAST* TheBlock;

  public:
    IterListAST(
      StyioAST* theList, 
      std::vector<IdAST*> tmpVars,
      StyioAST* block): 
      TheList(theList),
      TmpVars(tmpVars),
      TheBlock(block)
      {

      }

    StyioType hint() {
      return StyioType::IterList;
    }

    std::string toString(int indent = 0) {
      return std::string("Iter (List) { ") 
      + TheList -> toString()
      + " }";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Iter (List) { ") 
      + TheList -> toStringInline()
      + " }";
    }
};

/*
  IterRangeAST: Range >> {}
*/
class IterRangeAST : public StyioAST {
  StyioAST* TheRange;
  std::vector<IdAST*> TmpVars;
  StyioAST* TheBlock;

  public:
    IterRangeAST(
      StyioAST* theRange, 
      std::vector<IdAST*> tmpVars,
      StyioAST* block): 
      TheRange(theRange),
      TmpVars(tmpVars),
      TheBlock(block)
      {

      }

    IterRangeAST(
      StyioAST* theRange, 
      std::vector<IdAST*> tmpVars): 
      TheRange(theRange),
      TmpVars(tmpVars)
      {

      }

    StyioType hint() {
      return StyioType::IterRange;
    }

    std::string toString(int indent = 0) {
      return std::string("Iter (Range) { ") 
      + TheRange -> toString()
      + " }";
    }

    std::string toStringInline(int indent = 0) {
      return std::string("Iter (Range) { ") 
      + TheRange -> toStringInline()
      + " }";
    }
};

#endif