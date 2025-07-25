package org.example;

public class Employee {
  String name;
  int age;
  long personalCardId;
  long phoneNumber;
  Address address;

  public Employee(String name, int age, long personalCardId, long phoneNumber, Address address) {
    this.name = name;
    this.age = age;
    this.personalCardId = personalCardId;
    this.phoneNumber = phoneNumber;
    this.address = address;
  }

  public void print() {
    System.out.println("==========" + this.name + "========");

    if (this.age < 18) {
      System.out.println("Error: too young to have an account");
      return;
    }

    System.out.print(
        "name: " + this.name + '\n' +
            "age: " + this.age + '\n' +
            "personalCardId: " + this.personalCardId + '\n' +
            "phoneNumber: " + this.phoneNumber + '\n' +
            "address: {");
    this.address.print();
    System.out.println("}");
  }
}
