#include "CGApplication.h"
#include <iostream>
#include <stdexcept>

//
//// PROYECTO: Project11c
//// DESCRIPCI�N: Aplicaci�n gr�fica que incluye el c�lculo de sombras
////              con la t�cnica de Random sampling.
//
int main()
{
    CGApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}