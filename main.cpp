#include <iostream>
#include <cassert>
#include <cstddef>

using namespace std;

void print_in_hex(uint8_t byte); //ѕечать байт данных
void print_in_hex(const void* byte, size_t size);//ѕечать блока данных
void print_in_hinary(uint8_t byte);
void print_in_hinary(const void* byte, size_t size);

//1.2-3. »звлечь из байта младш и старш nibble как число от 0 до 15
char nibble_in_hex(uint8_t i){
    char digits[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    return digits[i];
    }

//1.4 Ќапечатать байт как два nibble
void print_in_hex(uint8_t byte){
    cout << nibble_in_hex(byte >> 4)
         << nibble_in_hex(byte & 0xf);
}

//1.5-6. ѕреоб void8 в uint8_t* и напечатать массив этих байт
const uint8_t* as_bytes(const void* data);

void
print_in_hex(const void* data, size_t size) {
    const uint8_t* bytes = as_bytes(data);
    for (size_t i = 0; i < size; i++) {
        print_in_hex(bytes[i]);

        if ((i + 1) % 16 == 0) {
            cout << '\n';
        }
        else {
            cout << ' ';
        }
    }
}

const uint8_t*
as_bytes(const void* data) {
return reinterpret_cast<const uint8_t*>(data);
}


//1.7 Ќапечатать баайт в двоичном виде
char
bit_digit(uint8_t byte, uint8_t bit) {
    if (byte & (0x1 << bit)) {
        return '1';
    }
    return '0';
}
//—делаем сидвиги на 7,6,.., 0 бит - циклом
void
print_in_binary(uint8_t byte) {
    for (uint8_t bit = 7; bit > 0; bit--){
        cout << bit_digit(byte, bit);
    }
    cout << bit_digit(byte, 0);
}
//«десь должна€ буть самопроверка по слайду из лекции

//1.8. Ќапечатать блок данных в дв виде
void //приведение типов в дв виде
print_in_binary(const void* data, size_t size) {
    const uint8_t* bytes = as_bytes(data);
    for (size_t i = 0; i < size; i++) {
        print_in_binary(bytes[i]);

        if ((i + 1) % 4 == 0) {
            cout << '\n';
        }
        else {
            cout << ' ';
        }
    }
}

void calc(uint16_t op1, char oper, uint16_t op2){
    print_in_hex (&op1, sizeof(op1)); //16-й вид
    cout << oper << " ";
    print_in_hex(&op2, sizeof(op2));
    uint16_t result16;
    if (oper == '&') {
        result16 = op1 & op2;
    }
    if (oper == '|') {
        result16 = op1 | op2;
    }
    cout << " = ";
    print_in_hex (&result16, sizeof(result16));
    cout << endl;

    print_in_binary (&op1, sizeof(op1)); //2-й вид
    cout << oper << " ";
    print_in_binary(&op2, sizeof(op2));
    uint16_t result2;
    if (oper == '&') {
        result2 = op1 & op2;
    }
    if (oper == '|') {
        result2 = op1 | op2;
    }
    if (oper == '^') {
        result2 = op1 ^ op2;
    }
    cout << " = ";
    print_in_binary (&result2, sizeof(result2));

}

struct Student {
    char name[17];
    uint16_t year;
    float sred;
    uint8_t gender :1;
    uint16_t course;
    Student* starosta;
};

int main()
{
    assert(nibble_in_hex(0x0) == '0');
    assert(nibble_in_hex(0x1) == '1');
    assert(nibble_in_hex(0x2) == '2');
    assert(nibble_in_hex(0x3) == '3');
    assert(nibble_in_hex(0x4) == '4');
    assert(nibble_in_hex(0x5) == '5');
    assert(nibble_in_hex(0x6) == '6');
    assert(nibble_in_hex(0x7) == '7');
    assert(nibble_in_hex(0x8) == '8');
    assert(nibble_in_hex(0x9) == '9');
    assert(nibble_in_hex(0xa) == 'a');
    assert(nibble_in_hex(0xb) == 'b');
    assert(nibble_in_hex(0xc) == 'c');
    assert(nibble_in_hex(0xd) == 'd');
    assert(nibble_in_hex(0xe) == 'e');
    assert(nibble_in_hex(0xf) == 'f');

    uint16_t u8 = 1045;
    uint16_t u81 = 125;
    calc (u8,'&', u81);

    Student Students[3]={
        {"Starosta", 1998, 4, 1, 1, nullptr},
        {"Dankov", 2000, 4, 1, 1},
        {"Tixonov", 2000, 4, 1, 1},
    };

    // адрес и размер массива, всех элементов массива
    cout << "\n";
    cout << "Address of Students: \t" << &Students << endl;
    cout << "Size of Students: \t" << sizeof(Students) << endl;
    cout << "Address of Students[1]: \t" << &Students[1] << endl;
    cout << "Size of Students[1]: \t" << sizeof(Students[1]) << endl;
    cout << "Address of Students[2]: \t" << &Students[2] << endl;
    cout << "Size of Students[2]: \t" << sizeof(Students[2]) << endl;
    cout << "Address of Students[3]: \t" << &Students[3] << endl;
    cout << "Size of Students[3]: \t" << sizeof(Students[3]) << endl;
    //адреса полей структуры
    cout << "Address of name: \t" << &Students[2].name << endl;
    cout << "Address of year: \t" << &Students[2].year << endl;
    cout << "Address of sred: \t" << &Students[2].sred << endl;
    cout << "Address of course: \t" << &Students[2].course << endl;
    //смещение от начала структуры
    cout << "Name is at offset: \t" << offsetof(Student, name) << endl; //—мещение от начала структуры
    cout << "Year is at offset: \t" << offsetof(Student, year) << endl;
    cout << "Sred is at offset: \t" << offsetof(Student, sred) << endl;
    cout << "Course is at offset: \t" << offsetof(Student, course) << endl;
    //размер полей структуры
    cout << "Size of name: \t" << sizeof(Students[2].name) << endl;
    cout << "Size of year: \t" << sizeof(Students[2].year) << endl;
    cout << "Size of sred: \t" << sizeof(Students[2].sred) << endl;
    cout << "Size of course: \t" << sizeof(Students[2].course) << endl;
    //шестнадцатеричное и двоичное представление полей структуры
    cout << "Year in hex: \t";
    print_in_hex(&Students[2].year, sizeof(Students[2].year));
    cout << endl;
    cout << "Sred in hex: \t";
    print_in_hex(&Students[2].sred, sizeof(Students[2].sred));
    cout << endl;
    cout << "Course in hex: \t";
    print_in_hex(&Students[2].course, sizeof(Students[2].course));
    cout << endl;
    cout << "Year in bin: \t";
    print_in_binary(&Students[2].year, sizeof(Students[2].year));
    cout << endl;
    cout << "Sred in bin: \t";
    print_in_binary(Students[2].sred);
    cout << endl;
    cout << "Course in bin: \t";
    print_in_binary(Students[2].course);
    cout << endl;
    //все элементы массива в шестнадцатеричном виде с указанием соответстви€ блоков байт пол€м структур

    cout << "Eear sred course \n";
    for (int i = 0; i < 3; i++)
    {
        print_in_hex(&Students[i].year, sizeof(Students[i].year));
        cout << "|";
        print_in_hex(&Students[i].sred, sizeof(Students[i].sred));
        cout << "|";
        print_in_hex(&Students[i].course, sizeof(Students[i].course));
        cout << endl;

    }
    return 0;
}

