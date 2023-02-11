#ifndef __OPCION_H__
#define __OPCION_H__

#define OPCION_1                    101

int opcion_correcta(const int opcion, char tecla)
{
    if (opcion == OPCION_1)
    {
        if (tecla == 'A' || tecla == 'a')
            return 1;
        if (tecla == 'B' || tecla == 'b')
            return 2;
        if (tecla == 'C' || tecla == 'c')
            return 3;
        if (tecla == 'E' || tecla == 'e')
            return 4;
    }
    else
        return (tecla == 'W' || tecla == 'w');
}

#endif // !__OPCION_H__