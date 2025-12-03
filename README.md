# Student-Record-System-C
# Student Record Management System (TCP Version)

This project is a simple **Student Record Management System** that can:

* Read student data from a CSV file.
* Perform basic operations like **list**, **search**, and **sort**.
* Send all student data from a **Sender program** to a **Receiver program** using **TCP socket communication**.
* Save the received data into a new CSV file.
* Measure basic performance statistics.

---

## 📌 Features

### **1. Core Student Operations**

* List all students
* Search student by ID
* Sort students by name

### **2. TCP Communication**

* Sender connects to Receiver using TCP.
* Sender transmits full student data.
* Receiver stores the data into `received.csv`.

---

## 🛠️ How to Run the Project

### ✔️ **1. Start the Receiver (Terminal 1)**

```
./receiver
```

You should see:

```
Server started... waiting for connection...
```

### ✔️ **2. Run the Sender (Terminal 2)**

```
./sender
```

Select:

```
5. Send Data to Receiver
```

You will see:

```
Connected to server
Data sent successfully
```

Receiver terminal will show:

```
Client connected!
Data received and saved to received.csv
```

---

## 📁 Input File

The sender reads student data from:

```
students.csv
```

Example format:

```
1,John,19,A
2,Asha,20,B
```

---

## 📊 Performance Metrics

Measured in the program:

* Number of records processed
* Time taken to load and parse CSV
* Time taken to sort records
* Time taken to transmit data over TCP
* Time taken to save received CSV file
* Memory usage (optional)

These results are printed in the terminal after execution.

---

## 📦 Tools Used

* **C Language**
* **TCP Sockets** (sender & receiver)
* **WSL / Linux environment**
* **Git & GitHub** for version control

---

## 📘 Summary

This project demonstrates:

* File handling in C
* Structs and arrays
* Sorting and searching
* Network programming basics
* Measuring simple performance metrics

It is a clean and simple implementation suitable for learning and academic submissions.

---

## ✨ Author

**Kavana Naik**
