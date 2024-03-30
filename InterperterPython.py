MAX_RESULT_LENGTH = 100
MAX_CODE_LENGTH = 100
MAX_VARIABLES = 50
variables = {}
def evaluate_expression(expr):
    return eval(expr, {}, variables)
def execute_statement(statement, depth):
    if depth > 3:
        raise ValueError("Maximum depth of nested conditionals exceeded")
    if "var" in statement:
        var_name, expr = statement.split("=")[0].split("var")[1].strip(), statement.split("=")[1].strip()
        result = evaluate_expression(expr)
        if len(str(result)) > MAX_RESULT_LENGTH or len(variables) >= MAX_VARIABLES:
            raise ValueError("Result length exceeds maximum allowed" if len(
                str(result)) > MAX_RESULT_LENGTH else "Maximum number of variables exceeded")
        variables[var_name] = result
        return result
    elif "if" in statement:
        condition, *body = statement.split(":")
        if evaluate_expression(condition.replace("if", "").strip()):
            [execute_statement(stmt.strip(), depth + 1) for stmt in body[0].strip().split("\n")]
    elif "while" in statement:
        condition, body = statement.split(":")
        condition = condition.replace("while", "").strip()
        body = body.strip().split("\n")
        while evaluate_expression(condition):
            [execute_statement(stmt.strip(), depth + 1) for stmt in body]
            break
def interpret(program):
    for stmt in program.split("\n"):
        if len(stmt.strip()) > MAX_CODE_LENGTH:
            raise ValueError("Program length exceeds maximum allowed")
        execute_statement(stmt.strip(), depth=0)
program = """var x = 3
var y = 12
var z = x + y
if z > 10:
    var result = z * 2
    if result < 20:
        var temp = result + 5
var flag = True
if flag == True:
    var flag_result = result - 15
var i = 50
while i < result:
    if i % 2 != 0:
        var temp = i * 3
    var j = 7
    while j < temp:
        var k = j + temp
        j = j + 1"""
interpret(program)
print("Variables after program execution:\n", "\n".join([f"{var}: {val}" for var, val in variables.items()]))