package org.example;

public class Address {
  String location;

  public Address(String location) {
    this.location = location;
  }

  public void print() {
    System.out.println(
        "location: " + this.location);
  }
}
