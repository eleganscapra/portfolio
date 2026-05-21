# 1. LA APROXIMACIÓN DECIDIBLE
def analizador_de_signos(codigo_fuente):
    """
    Esta función simula el "Analizador" del documento. 
    Intenta predecir el resultado de un programa analizando su texto.
    Como el problema es indecidible, esta es solo una aproximación.
    """
    if "return 1" in codigo_fuente:
        return "+"
    elif "return -1" in codigo_fuente:
        return "-"
    else:
        # Si el código es complejo, el analizador se rinde y arroja "top" (desconocido)
        return "top (desconocido)"


# 2. LA FUNCIÓN TESTIGO (Witness Function)
def funcion_testigo(analizador):
    """
    Esta función ilustra la teoría central del artículo:
    Toma la implementación de la aproximación y genera un caso (testigo)
    que expone la imprecisión del analizador.
    """
    # Algorítmicamente construimos un programa que sabemos que dará 
    # un resultado positivo (1), pero que está escrito de una forma 
    # que engañará a la lógica simple de nuestro analizador.
    testigo_impreciso = """
def funcion_matematica():
    x = 10
    while x > 0:
        x -= 1
    # x termina siendo 0. 0 + 1 es 1 (positivo)
    return x + 1 
"""
    # Ponemos a prueba la aproximación con el testigo
    resultado_aproximacion = analizador(testigo_impreciso)
    
    return testigo_impreciso, resultado_aproximacion

# --- EJECUCIÓN ---
print("--- TESTIFICABILIDAD DE PROBLEMAS INDECIDIBLES ---\n")

codigo_generado, resultado = funcion_testigo(analizador_de_signos)

print("1. Código Testigo Generado:")
print(codigo_generado)
print("2. Resultado de la Aproximación (Analizador):", resultado)
print("3. Resultado Real: El programa siempre devuelve 1 (+).")
print("\n¡Conclusión! La función testigo demostró con éxito la imprecisión de la aproximación.")