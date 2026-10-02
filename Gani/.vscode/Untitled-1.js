/*
    Student Management System
    Using JavaScript OOP and JSON
*/


// ========================================
// Student Class
// ========================================

class Student {

    constructor(id, name, course, marks) {

        this.id = id;
        this.name = name;
        this.course = course;
        this.marks = marks;

    }


    // Method to calculate grade

    getGrade() {

        if (this.marks >= 90) {
            return "A+";
        }

        else if (this.marks >= 80) {
            return "A";
        }

        else if (this.marks >= 70) {
            return "B";
        }

        else if (this.marks >= 60) {
            return "C";
        }

        else if (this.marks >= 50) {
            return "D";
        }

        else {
            return "F";
        }

    }

}


// ========================================
// Student Management Class
// ========================================

class StudentManager {

    constructor() {

        this.students = [];

    }


    // Add student

    addStudent(student) {

        this.students.push(student);

    }


    // Delete student

    deleteStudent(id) {

        this.students =
            this.students.filter(
                student => student.id !== id
            );

    }


    // Search student

    searchStudent(id) {

        return this.students.find(
            student => student.id === id
        );

    }


    // Convert students into JSON

    convertToJSON() {

        return JSON.stringify(this.students);

    }

}


// Create StudentManager object

const manager = new StudentManager();


// ========================================
// Add Student Event
// ========================================

document
    .getElementById("studentForm")
    .addEventListener("submit", function(event) {

        event.preventDefault();


        // Get form values

        const id =
            document.getElementById("studentId").value;

        const name =
            document.getElementById("studentName").value;

        const course =
            document.getElementById("course").value;

        const marks =
            Number(
                document.getElementById("marks").value
            );


        // Check duplicate ID

        if (manager.searchStudent(id)) {

            showMessage(
                "Student ID already exists!",
                "red"
            );

            return;

        }


        // Create Student object

        const student =
            new Student(
                id,
                name,
                course,
                marks
            );


        // Add student

        manager.addStudent(student);


        // Display records

        displayStudents();


        // Show success message

        showMessage(
            "Student added successfully!",
            "green"
        );


        // Clear form

        document
            .getElementById("studentForm")
            .reset();

    });


// ========================================
// Display Students
// ========================================

function displayStudents(studentList = manager.students) {

    const table =
        document.getElementById("studentTable");

    table.innerHTML = "";


    studentList.forEach(student => {

        const row =
            document.createElement("tr");


        row.innerHTML = `

            <td>${student.id}</td>

            <td>${student.name}</td>

            <td>${student.course}</td>

            <td>${student.marks}</td>

            <td>${student.getGrade()}</td>

            <td>

                <button
                    class="delete-btn"
                    onclick="deleteStudent('${student.id}')">

                    Delete

                </button>

            </td>

        `;


        table.appendChild(row);

    });

}


// ========================================
// Search Student
// ========================================

function searchStudent() {

    const id =
        document.getElementById("searchInput")
        .value.trim();


    if (id === "") {

        displayStudents();

        return;

    }


    const student =
        manager.searchStudent(id);


    if (student) {

        displayStudents([student]);

        showMessage(
            "Student found!",
            "green"
        );

    }

    else {

        displayStudents([]);

        showMessage(
            "Student not found!",
            "red"
        );

    }

}


// ========================================
// Delete Student
// ========================================

function deleteStudent(id) {

    manager.deleteStudent(id);

    displayStudents();

    showMessage(
        "Student deleted successfully!",
        "green"
    );

}


// ========================================
// Display Message
// ========================================

function showMessage(text, color) {

    const message =
        document.getElementById("message");

    message.textContent = text;

    message.style.color = color;

}


// ========================================
// Initial Display
// ========================================

displayStudents();


// ========================================
// JSON Representation Example
// ========================================

console.log(
    "Student Data in JSON:",
    manager.convertToJSON()
);


