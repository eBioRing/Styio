// [C++ STL]
#include <string>
#include <memory>
#include <vector>

// [Styio]
#include "AST.hpp"
#include "../StyioUtil/Util.hpp"
#include "../StyioToken/Token.hpp"

std::string TrueAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { }");
}

std::string FalseAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { }");
}

std::string NoneAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { }");
}

std::string EndAST::toString(int indent, bool colorful) {
  return std::string("EOF { }");
}

std::string EmptyAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { }");
}

std::string EmptyBlockAST::toString(int indent, bool colorful) {
  return std::string("Block (Empty) { ")
    + " } ";
}

std::string BreakAST::toString(int indent, bool colorful) {
  return std::string("Break { }");
}

std::string PassAST::toString(int indent, bool colorful) {
  return std::string("Pass { }");
}

std::string ReturnAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + " { "
    + Expr -> toStringInline(indent + 1, colorful)
    + " }";
}

std::string CommentAST::toString(int indent, bool colorful) {
  return std::string("Comment { ") + Text + " }";
}

std::string IdAST::toString(int indent, bool colorful) {
  return std::string("id { ") + Id + " }";
}

std::string ArgAST::toString(int indent, bool colorful) {
  return std::string("arg { ") + Id ->toString(indent + 1, colorful) + " }";
}

std::string KwArgAST::toString(int indent, bool colorful) {
  return std::string("kwargs { ") + Id ->toString(indent + 1, colorful) + " }";
}

std::string VarsTupleAST::toString(int indent, bool colorful) {
  if (Vars.empty()) 
  {
    return reprStyioType(this -> hint(), colorful) + std::string(" { }");
  }
  else 
  {
    std::string outstr;
    for (std::vector<std::unique_ptr<StyioAST>>::iterator it = Vars.begin(); 
      it != Vars.end(); 
      ++it
    ) {
      outstr += make_padding(indent, " ") + (*it) -> toString(indent + 1, colorful);
      if (it != (Vars.end() - 1)) { outstr += "\n"; }
    }
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
      + outstr
      + "}";
  }
}

std::string TypeAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { ") + Type + " }";
}

std::string TypedVarAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { ") 
  + Id -> toStringInline(indent + 1, colorful) 
  + " "
  + Type -> toStringInline(indent + 1, colorful) 
  + " }";
}

std::string IntAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + " { " + Value + " }";
}

std::string FloatAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + " { " + Value + " }";
}

std::string CharAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + " { \'" + Value + "\' }";
}

std::string StringAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + " { \"" + Value + "\" }";
}

std::string FmtStrAST::toString(int indent, bool colorful) {
  std::string elemstr = "";
  for (size_t i = 0; i < Fragments.size(); i++) {
    elemstr += make_padding(indent, " ") + "\""+ Fragments.at(i) + "\"\n"; }
  
  for (std::vector<std::unique_ptr<StyioAST>>::iterator it = Exprs.begin(); 
    it != Exprs.end(); 
    ++it) {
    elemstr += make_padding(indent, " ") + (*it) -> toString(indent + 1, colorful);
    if (it != (Exprs.end() - 1)) { elemstr += "\n"; } }
  return reprStyioType(this -> hint(), colorful) + " {\n" + elemstr + "}";
}

std::string ExtPathAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { ") + Path -> toStringInline(indent + 1, colorful) + " }";
}

std::string ExtLinkAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { }");
}

std::string ListAST::toString(int indent, bool colorful) {
  std::string ElemStr;

  for(int i=0; i < Elems.size(); i++) {
    ElemStr += make_padding(indent + 1, " ") + Elems[i] -> toString(indent + 1, colorful);
    if (i != (Elems.size() - 1)) { ElemStr += "\n"; }
  };

  return reprStyioType(this -> hint(), colorful) + std::string(" [\n")
    + ElemStr
    + "]";
}

std::string TupleAST::toString(int indent, bool colorful) {
  std::string ElemStr;

  for (int i=0; i < Elems.size(); i++) {
    ElemStr += make_padding(indent + 1, " ") + Elems[i] -> toString(indent + 1, colorful);
    if (i != (Elems.size() - 1)) { ElemStr += "\n"; } }

  return reprStyioType(this -> hint(), colorful) + std::string(" (\n")
    + ElemStr
    + ")";
}


std::string SetAST::toString(int indent, bool colorful) {
  std::string ElemStr;

  for (int i=0; i < Elems.size(); i++) {
    ElemStr += make_padding(indent + 1, " ") + Elems[i] -> toString(indent + 1, colorful) + "\n";
    
    if (i != (Elems.size() - 1)) { ElemStr += "\n"; }
  }

  return reprStyioType(this -> hint(), colorful) + std::string(" [\n")
    + ElemStr
    + "]";
}

std::string RangeAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
    + make_padding(indent, " ") + "Start: " + StartVal -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "End  : " + EndVal -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Step : " + StepVal -> toString(indent + 1, colorful)
    + "}";
}

std::string SizeOfAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { ") 
  + Value -> toStringInline(indent + 1, colorful)
  + " }";
}

std::string BinOpAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" {")
    + "\n"
    + make_padding(indent, " ") + "LHS: " + LHS -> toString(indent + 1, colorful) 
    + "\n"
    + make_padding(indent, " ") + "RHS: " + RHS -> toString(indent + 1, colorful) 
    + "}";
}

std::string BinCompAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + " " + reprToken(CompSign) + std::string(" {\n")
    + make_padding(indent, " ") + "LHS: " + LhsExpr -> toString() 
    + "\n"
    + make_padding(indent, " ") + "RHS: " + RhsExpr -> toString()
    + "}";
}

std::string CondAST::toString(int indent, bool colorful) {
  if (LogicOp == LogicType::AND
      || LogicOp == LogicType::OR
      || LogicOp == LogicType::XOR)
  {
    return reprStyioType(this -> hint(), colorful) + " {\n"
    + make_padding(indent, " ") + "Op: " + reprToken(LogicOp) 
    + "\n"
    + make_padding(indent, " ") + "LHS: " + LhsExpr -> toString(indent + 1, colorful) 
    + "\n"
    + make_padding(indent, " ") + "RHS: " + RhsExpr -> toString(indent + 1, colorful)
    + "}";
  }
  else
  if (LogicOp == LogicType::NOT)
  {
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
    + make_padding(indent, " ") + "Op: " + reprToken(LogicOp) 
    + "\n"
    + make_padding(indent, " ") + "Value: " + ValExpr -> toString(indent + 1, colorful)
    + "}";
  }
  else
  if (LogicOp == LogicType::RAW)
  {
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
    + make_padding(indent, " ") + ValExpr -> toString(indent + 1, colorful)
    + "}";
  }
  else
  {
    return reprStyioType(this -> hint(), colorful) + " { Undefined! }";
  }
}

std::string CallAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + " { }";
}

std::string ListOpAST::toString(int indent, bool colorful) {
  switch (OpType)
  {
  case StyioType::Access:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Key: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  
  case StyioType::Access_By_Index:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Index: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  case StyioType::Access_By_Name:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Name : " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  
  case StyioType::Get_Index_By_Value:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Index: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  case StyioType::Get_Indices_By_Many_Values:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Index: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  case StyioType::Append_Value:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Value: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;  
  case StyioType::Insert_Item_By_Index:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Index: " + Slot1 -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Value: " + Slot2 -> toString(indent + 1, colorful)
    + "}";
    break;
  case StyioType::Remove_Item_By_Index:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Index: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  case StyioType::Remove_Item_By_Value:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Value: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  case StyioType::Remove_Items_By_Many_Indices:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Index: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  case StyioType::Remove_Items_By_Many_Values:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Value: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  case StyioType::Get_Reversed:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful)
    + "}";
    break;
  case StyioType::Get_Index_By_Item_From_Right:
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + TheList -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Index: " + Slot1 -> toString(indent + 1, colorful)
    + "}";
    break;
  
  default:
    return reprStyioType(this -> hint(), colorful) + std::string(" { undefined }"); 
    break;
  }
  
  return reprStyioType(this -> hint(), colorful) + std::string(" { undefined }"); 
}

std::string ResourceAST::toString(int indent, bool colorful) {
  std::string varStr;

  for (std::vector<std::unique_ptr<StyioAST>>::iterator it = Resources.begin(); 
    it != Resources.end(); 
    ++it ) {
      varStr += make_padding(indent, " ");
      varStr += (*it) -> toStringInline();
      if (it != (Resources.end() - 1)) { varStr += "\n"; } 
    }
  
  return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
    + varStr
    + "}";
}

std::string FlexBindAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + "Var: " + varId -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Val: " + valExpr -> toString(indent + 1, colorful)
    + "}";
}

std::string FinalBindAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + "Var: " + varId -> toString(indent) + "\n"
    + make_padding(indent, " ") + "Val: " + valExpr -> toString(indent) 
    + "}";
}

std::string StructAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" {") 
    + "}";
}

std::string ReadFileAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + "Var: " + varId -> toString(indent + 1) + "\n"
    + make_padding(indent, " ") + "Val: " + valExpr -> toString(indent + 1) 
    + "}";
}

std::string PrintAST::toString(int indent, bool colorful) {
  std::string outstr;

  for (std::vector<std::unique_ptr<StyioAST>>::iterator it = Exprs.begin(); 
    it != Exprs.end(); 
    ++it ) {
    outstr += make_padding(indent, " ") + (*it) -> toString(indent + 1, colorful);
    if (it != (Exprs.end() - 1)) { outstr += "\n"; }
  }

  return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
    + outstr
    + "}";
}

std::string ExtPackAST::toString(int indent, bool colorful) {
  std::string pacPathStr;

  for(int i = 0; i < PackPaths.size(); i++) {
    pacPathStr += std::string(2, ' ') + "| ";
    pacPathStr += PackPaths[i];
    pacPathStr += "\n";
  };
  
  return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
    + pacPathStr
    + "\n} ";
}

std::string BlockAST::toString(int indent, bool colorful) {
  std::string stmtStr;

  for (std::vector<std::unique_ptr<StyioAST>>::iterator it = Stmts.begin(); 
    it != Stmts.end(); 
    ++it) {
    stmtStr += make_padding(indent, " ") + (*it) -> toString(indent + 1, colorful);
    if (it != (Stmts.end() - 1)) { stmtStr += "\n"; }
  }

  return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
    + stmtStr
    + "}";
}

std::string CasesAST::toString(int indent, bool colorful) {
  std::string stmtStr = "";

  for (std::vector<std::tuple<std::unique_ptr<StyioAST>, std::unique_ptr<StyioAST>>>::iterator it = Cases.begin(); 
    it != Cases.end(); 
    ++it ) {
    stmtStr += make_padding(indent, " ") + "Left : " + std::get<0>(*it) -> toString(indent + 1, colorful) + "\n";
    stmtStr += make_padding(indent, " ") + "Right: " + std::get<1>(*it) -> toString(indent + 1, colorful) + "\n";
  }

  return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
    + stmtStr
    + make_padding(indent, " ") + "Default: " + LastExpr -> toString(indent + 1, colorful);
    + "}";
}

std::string CondFlowAST::toString(int indent, bool colorful) {
  if (WhatFlow == StyioType::CondFlow_True
    || WhatFlow == StyioType::CondFlow_False)
  {
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + CondExpr -> toStringInline(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Then: " + ThenBlock -> toString(indent + 1, colorful)
    + "}";
  }
  else if (WhatFlow == StyioType::CondFlow_Both)
  {
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + CondExpr -> toStringInline(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Then: " + ThenBlock -> toString(indent + 1, colorful) + "\n"
    + make_padding(indent, " ") + "Else: " + ElseBlock -> toString(indent + 1, colorful)
    + "}";
  }
  else
  {
    return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
    + make_padding(indent, " ") + CondExpr -> toStringInline(indent + 1, colorful)
    + "}";
  }
}

std::string CheckEqAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" { ") 
  + Value -> toString(indent + 1, colorful)
  + " }";
}

std::string CheckIsInAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
  + make_padding(indent, " ") + Iterable -> toString(indent + 1, colorful)
  + "}";
}

std::string FromToAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" {")
  + "\n" 
  + make_padding(indent, " ") + "From: " + FromWhat -> toString(indent + 1, colorful)
  + "\n" 
  + make_padding(indent, " ") + "To: " + ToWhat -> toString(indent + 1, colorful)
  + "}";
}

std::string ForwardAST::toString(int indent, bool colorful) {
  switch (Type)
  {
  case StyioType::Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + "Run: " + ThenExpr -> toString(indent + 1, colorful) 
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::If_Equal_To_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n")
      + make_padding(indent, " ") + ExtraEq -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + "Run: " + ThenExpr -> toString(indent + 1, colorful) 
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::If_Is_In_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + ExtraIsin -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + "Run: " + ThenExpr -> toString(indent + 1, colorful) 
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::Cases_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + "Cases: " + ThenExpr -> toString(indent + 1, colorful) + "\n"
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::If_True_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + ExtraCond -> toString(indent + 1, colorful)
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::If_False_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + ExtraCond -> toString(indent + 1, colorful)
      + "}";
    }
    // You should NOT reach this line!
    break;
  
  case StyioType::If_Both_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + ExtraCond -> toString(indent + 1, colorful)
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::Fill_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + TmpVars -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + "Run: " + ThenExpr -> toString(indent + 1, colorful) 
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::Fill_If_Equal_To_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + TmpVars -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + ExtraEq -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + "Run: " + ThenExpr -> toString(indent + 1, colorful) 
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::Fill_If_Is_in_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + TmpVars -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + ExtraIsin -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + "Run: " + ThenExpr -> toString(indent + 1, colorful) 
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::Fill_Cases_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + TmpVars -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + "Cases: " + ThenExpr -> toString(indent + 1, colorful) + "\n"
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::Fill_If_True_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + TmpVars -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + ExtraCond -> toString(indent + 1, colorful)
      + "}";
    }
    // You should NOT reach this line!
    break;
  case StyioType::Fill_If_False_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + TmpVars -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + ExtraCond -> toString(indent + 1, colorful)
      + "}";
    }
    // You should NOT reach this line!
    break;
  
  case StyioType::Fill_If_Both_Forward:
    {
      return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
      + make_padding(indent, " ") + TmpVars -> toString(indent + 1, colorful) + "\n"
      + make_padding(indent, " ") + ExtraCond -> toString(indent + 1, colorful)
      + "}";
    }
    // You should NOT reach this line!
    break;
  default:
    break;
  }
  return reprStyioType(this -> hint(), colorful) + std::string(" { Undefined }");
}

std::string InfiniteAST::toString(int indent, bool colorful) {
  switch (WhatType)
  {
  case InfiniteType::Original:
    return reprStyioType(this -> hint(), colorful) + std::string(" { }");
    // You should NOT reach this line!
    break;
  
  case InfiniteType::Incremental:
    return reprStyioType(this -> hint(), colorful) + std::string(" {")
      + "\n" 
      + "|" + std::string(2 * indent, '-') + "| Start: "
      + Start -> toString(indent + 1, colorful) 
      + "\n"
      + "|" + std::string(2 * indent, '-') + "| Increment: "
      + IncEl -> toString(indent + 1, colorful) 
      + "\n"
      + "}";
    // You should NOT reach this line!
    break;
  
  default:
    break;
  }
  return reprStyioType(this -> hint(), colorful) + std::string(" { Undefined! }");
}

std::string FuncAST::toString(int indent, bool colorful) {
  std::string extra = "";

  if (FisFinal) { extra = " (Final)"; }
  else { extra = " (Flexible)"; }

  std::string output = reprStyioType(this -> hint(), colorful, extra) + " {\n";
  output += make_padding(indent, " ") + "Name: " + FName -> toString(indent + 1, colorful) + "\n";
  output += make_padding(indent, " ") + Forward -> toString(indent + 1, colorful);
  output += "}";
  return output;
}

std::string LoopAST::toString(int indent, bool colorful) {
  std::string output = reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
  + make_padding(indent, " ") + Forward -> toString(indent + 1, colorful) 
  + "}";

  return output;
}

std::string IterAST::toString(int indent, bool colorful) {
  return reprStyioType(this -> hint(), colorful) + std::string(" {\n") 
  + make_padding(indent, " ") + Collection -> toStringInline(indent + 1, colorful)
  + "}";
}
