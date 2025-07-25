package org.example;

public class Bank {
  String accountId;
  double balance;
  String accountType;

  public Bank(String accountId, double balance, String accountType) {
    this.accountId = accountId;
    this.accountType = accountType;

    // a 2% tax
    double balancAfterTaxes = balance * 0.02;
    double newBalance = balance - balancAfterTaxes;

    System.out.println("balance after taxes: " + newBalance);
  }
}
