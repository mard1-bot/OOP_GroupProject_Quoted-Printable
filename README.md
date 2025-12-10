# Проект: Кодирование Quoted-Printable

Этот проект реализует алгоритмы **кодирования** и **декодирования** формата Quoted-Printable согласно спецификации MIME (RFC 1521).

---

## 📌 Цель работы

Изучить алгоритм кодирования и декодирования Quoted-Printable и разработать приложение, реализующее оба механизма.

---

## 📁 Содержание

1. Цель работы
2. Компиляция программы
3. Команда для шифрования и расшифровки
4. Практические примеры

---

## 🔧 Компиляция программы

Сохраните код в файл `qpdecode.cpp`, затем используйте команду компиляции для вашей системы.

### Windows (MinGW)

```bash
g++ -o qpdecode.exe qpdecode.cpp
```

### Windows (Visual Studio)

```bash
cl /EHsc qpdecode.cpp
```

### Linux / macOS

```bash
g++ -o qpdecode qpdecode.cpp
```

### Рекомендуемая оптимизация

```bash
g++ -O2 -o qpdecode qpdecode.cpp
```

---

---

# 🔐 Команда для шифрования и расшифровки

---

## Универсальная команда `qp`

Утилита `qp` - основная команда для кодирования и декодирования. Она поддерживает флаги, позиционные аргументы и работу с файлами.

### Справка

```bash
qp --help
qp -h
```

### Примеры использования (в рамках `qp`)

- Кодирование строки:

```bash
qp --encrypt "Hello World"
qp -e "Secret data"
```

- Декодирование строки:

```bash
qp --decrypt "Hello=20World"
qp -d "=48=65=6C=6C=6F"
```

- Работа с файлами:

```bash
qp -e -f input.txt -o encoded.qp
qp -d -f encoded.qp -o decoded.txt
```

### Позиционные аргументы

Вместо флагов можно использовать позиционные аргументы — первый аргумент указывает действие (`encrypt`/`decrypt`):

```bash
qp encrypt "Hello World"
qp decrypt "Hello=20World"
qp encode file.txt
qp decode file.qp
```

---

# 📘 Примеры использования 

### Кодирование текста

```
Input:  Привет мир
Output: =D0=9F=D1=80=D0=B8=D0=B2=D0=B5=D1=82=20=D0=BC=D0=B8=D1=80
```

### Декодирование текста

```
Input:  Hello=20World
Output: Hello World
```

### Кодирование файла

```bash
qp -e -f article.txt -o article.qp
```

### Декодирование файла

```bash
qp -d -f message.qp
```

