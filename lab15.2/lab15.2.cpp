#include <iostream>
using namespace std;

void encryptor(char* file_path, char* ou_file_path, int RecordLength, int Shift)
{
    FILE* fl = fopen(file_path, "r");
    FILE* fm = fopen(ou_file_path, "w");
    int i, *a, n, j = 0, l, w = 0;
    int byte = 8;
    RecordLength *= byte; //для удобство умножаю на байт, получаю количество двоичных символов в слове
    a = new int[2 * RecordLength];//дублирую массив для дублирования символов, можно создать отдельный массив, но лучше так я думаю

    while (w == 0)
    {
        n = getc(fl);
        if (n == EOF)
        {
            w = 1;
            while (j < RecordLength && j != 0)//если достигли конец файла, но слово не собрано до конца
            {
                n = ' ';
                for (l = byte - 1; l >= 0; l--)//разбираем пробел на двоичный код
                {
                    a[j + l] = n % 2;
                    a[j + l + RecordLength] = a[j + l];
                    n /= 2;
                }
                j += byte;
            }
        }
        else
        {
            for (l = byte - 1; l >= 0; l--)//разбираем символ на двоичный код
            {
                a[j + l] = n % 2;
                a[j + l + RecordLength] = a[j + l];
                n /= 2;
            }
            j += byte;
        }

        if (j == RecordLength)//если слово собрано полностью
        {

            if (Shift > 0) //сдвиг влево
                for (i = 0; i < RecordLength; i++) a[i] = a[i + Shift];
            else //сдвиг вправо
                for (i = 0; i < RecordLength; i++) a[i] = a[i + RecordLength + Shift];

            for (i = 0; i < RecordLength; i += byte)//проходим по символам в слове
            {
                n = 0;
                l = 1;
                for (j = byte - 1; j >= 0; j--)//перевод символа из двоичного кода в число
                {
                    n += a[i + j] * l;
                    l *= 2;
                }
                fprintf(fm, "%c", n);
                j = 0;
            }
        }
    }
    fclose(fl); fclose(fm);
}

int main()
{
    char file_path[] = "text.txt";
    char ou1_file_path[] = "encrypted_text.txt";
    char ou2_file_path[] = "decrypted_text.txt";
    int n, m;
    cout << "Введите длину шифруемой части текста и размер сдвига через пробел: ";
    scanf("%d%d", &n, &m);

    encryptor(file_path, ou1_file_path, n, -m);//вызов с шифрованием, минус потому что я сдвиги сделал наоборот, но это не критично
    encryptor(ou1_file_path, ou2_file_path, n, m);//соответственно дешифровка без минуса потому что в шифровщике был минус, т.е. функция с минусом является
    //обратной к функции без минуса :)
}