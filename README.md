# Calculator
A small project to improve my C design and coding skills

CLI Mathematical Expression Parser & Evaluator in CA lightweight C-based command-line interface (CLI) tool designed to parse and evaluate complex mathematical expressions. 
It tokenizes raw input strings, handles unary operations, translates infix notation to Reverse Polish Notation (RPN) using Dijkstra's Shunting Yard algorithm, and computes the final result using a stack-based evaluator.

Key FeaturesCustom Tokenizer (Lexer):Parses integers and floating-point values (supports both . and , as decimal separators).

- Automatically ignores whitespace.
- Correctly identifies unary minus signs attached to numbers (e.g., -5 + 3).
- Unary Negative Parentheses Processing:Dynamically expands expressions like -(a + b) into -1 * (a + b) during tokenization.
- Shunting Yard Algorithm:Converts standard infix expressions into Reverse Polish Notation (RPN) while preserving strict operator precedence and bracket nesting.
- Stack-Based Evaluation:Evaluates post-fix token queues sequentially in O(n) time complexity.
- Syntax Error Handling:Validates parenthetical balance prior to parsing.
- Catches division-by-zero, invalid characters, and malformed decimals (e.g., multiple decimal points).
  
Architecture & PipelineThe evaluation lifecycle processes inputs through a structured four-stage compilation pipeline:
PlaintextInput String -> Lexer (Tokenization) -> Syntax Validation -> Shunting Yard Parser -> Postfix Evaluator -> Result

1. Lexing (gettoken)Scans the input buffer character by character and emits Token structures. When encountering a negative sign before a parenthesis (e.g., -(5 * 2)), it automatically injects a -1 scalar and a * operator into the token stream.
   
2. Syntax Validation (valid_parenthesis)Performs a preliminary scan to ensure opening ( and closing ) parentheses are strictly balanced before building the execution stack.

3.Parsing (shutingyard)Re-orders the token stream into postfix notation using an operator stack based on operator precedence:OperatorDescriptionPriority Level*, /Multiplication & DivisionHigh (1)+, -Addition & SubtractionLow (0).

4. Postfix Evaluation (post_exp & result)Consumes the RPN queue and computes intermediate scalar results using a dynamic operand stack.

Requirements & CompilationPrerequisitesAny standard C99-compliant C compiler (gcc, clang, MSVC).Standard C libraries (stdio.h, stdbool.h, stdlib.h).Building and RunningBash# Compile using GCC
gcc -o calculator main.c Mylib.c -Wall

# Run the executable
./calculator
Example UsagePlaintextExpression : 4 - -(5 * 2)
Result     : 14

==========================================

Expression : -3.5 + 10 / 2
Result     : 1.5

==========================================

Expression : q
Exit...
