
# Student Database Management System

## Project Overview

The **Student Database Management System** (DBMS) is a console-based application designed to manage student records efficiently. It provides functionalities to add, update, search, and delete student records, ensuring data integrity and ease of use. The project is written in C and utilizes static arrays to store the student data, with future improvements planned for scalability and additional features.

## Features

- **Add Students:**
  - Manually input student details (ID, first name, last name, GPA, and courses).
  - Load student data from a text file for batch processing.
- **Search Students:**
  - Search by student ID, first name, or course ID.
- **Update Students:**
  - Modify existing student records (ID, name, GPA, courses).
- **Delete Students:**
  - Remove student records by ID.
- **Display All Students:**
  - View all student records with detailed information.
  
## Technologies Used

- **Language**: C
- **Data Storage**: Static arrays

## Project Structure

```
/student
├── student.c        # Main program logic
├── student.h        # Header file with function declarations
├── data.txt          # Example text file for batch student data input
├── Makefile              # Build script (if using make for compilation)
└── README.md             # Project overview and usage instructions
```

## How to Use

### 1. Clone the Repository

```
git clone https://github.com/your-username/student-dbms.git
cd student-dbms
```

### 2. Compilation

You can compile the project using `gcc` or any other C compiler:

```bash
gcc -o StudentDataBase student.c main.c
```

Alternatively, if a `Makefile` is included:

```bash
make
```

### 3. Running the Program

After compiling, you can run the program from the terminal:

```bash
./student
```

### 4. Features Overview

#### Adding Students Manually

- The program will prompt you to input student details such as ID, name, GPA, and course IDs.
- Example:
  
  ```
  Enter student id: 123
  Enter student first name: John
  Enter student last name: Doe
  Enter student GPA: 3.8
  Enter course 1 ID: 101
  Enter course 2 ID: 102
  Enter course 3 ID: 103
  ```

#### Adding Students from a Text File

- The program can also read student data from a text file. You can provide the path to a file containing student information, with each student’s details on a new line.
- Example file content (`students.txt`):

  ```
  123 John Doe 3.8 101 102 103
  124 Jane Smith 3.9 104 105 106
  ```

#### Searching for Students

- You can search for a student by their ID, first name, or course ID.

  Example:
  
  ```
  Search by student ID: 123
  ```

#### Updating Student Records

- Allows updating student details by providing the student ID.

#### Deleting Students

- You can delete a student by entering their ID.

  Example:

  ```
  Delete student with ID: 123
  ```

#### Display All Students

- This command displays all student records stored in the system.

## Input Validation

- **Duplicate ID Check**: The system checks whether a student ID already exists to prevent duplicate entries.
- **GPA Validation**: Ensures that GPA values are between 0.0 and 4.0.

## Future Improvements

- **Dynamic Memory Allocation**: Improve the system to handle a larger number of students.
- **Database Integration**: Integrate SQLite or MySQL for better scalability and persistent data storage.
- **Graphical User Interface (GUI)**: Develop a GUI to improve the user experience.
- **User Authentication**: Add user login and roles for secured access to the system.

## Report & Video

- **Report**: [Download the project report](https://drive.google.com/drive/folders/1WXWFNaMpJc_ZzF02iEWsGzPXgRBx5rnx?usp=drive_link)
- **Video**: [Watch the program in action](https://drive.google.com/drive/folders/17sfAB7xVPdkj4__VAaFt0_8nObihoKlF)

## Contribution

Contributions to this project are welcome! If you want to report issues or request new features, feel free to create a pull request or open an issue in the repository.
