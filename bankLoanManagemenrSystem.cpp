#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
class Loan
{
private:
    std::string borrowerName;
    double loanAmount;
    double interestRate;
    bool isPaid;

public:
    Loan(std::string name, double amount, double rate)
        : borrowerName(name), loanAmount(amount), interestRate(rate), isPaid(false) {}
    void makePayment(double payment)
    {
        if (isPaid)
        {
            std::cout << "Loan is already paid off!\n";
            return;
        }

        if (payment >= loanAmount)
        {
            loanAmount = 0;
            isPaid = true;
            std::cout << "Loan paid off completely!\n";
        }
        else
        {
            loanAmount -= payment;
            std::cout << "Payment made: $" << payment << "\nRemaining balance: $" << loanAmount << "\n";
        }
    }
    void displayLoanInfo() const
    {
        std::cout << "Borrower Name: " << borrowerName << "\n";
        std::cout << "Loan Amount: $" << std::fixed << std::setprecision(2) << loanAmount << "\n";
        std::cout << "Interest Rate: " << interestRate * 100 << "%\n";
        std::cout << "Payment Status: " << (isPaid ? "Paid Off" : "Outstanding") << "\n";
    }
    bool isLoanPaid() const
    {
        return isPaid;
    }

    double getRemainingBalance() const
    {
        return loanAmount;
    }
};
class LoanManagementSystem
{
private:
    std::vector<Loan> loans;

public:
    void addLoan(const Loan &loan)
    {
        loans.push_back(loan);
        std::cout << "Loan added successfully!\n";
    }
    void makePayment(int index, double payment)
    {
        if (index >= 0 && index < loans.size())
        {
            loans[index].makePayment(payment);
        }
        else
        {
            std::cout << "Invalid loan index!\n";
        }
    }
    void displayLoans() const
    {
        if (loans.empty())
        {
            std::cout << "No loans available.\n";
            return;
        }

        for (size_t i = 0; i < loans.size(); ++i)
        {
            std::cout << "\nLoan Index: " << i + 1 << "\n";
            loans[i].displayLoanInfo();
        }
    }
    size_t getLoansCount() const
    { // Added method to get the count of loans
        return loans.size();
    }
};
int main()
{
    LoanManagementSystem lms;

    int choice;

    do
    {
        std::cout << "\n=== Bank Loan Management System ===\n";
        std::cout << "1. Add Loan\n";
        std::cout << "2. Make Payment\n";
        std::cout << "3. Display Loans\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        switch (choice)
        {
        case 1:
        {
            std::string name;
            double amount, rate;

            std::cin.ignore(); // Clear the input buffer
            std::cout << "Enter borrower's name: ";
            getline(std::cin, name); // Use getline to allow spaces in names

            std::cout << "Enter loan amount: ";
            std::cin >> amount;

            std::cout << "Enter interest rate (as a decimal): ";
            std::cin >> rate;

            lms.addLoan(Loan(name, amount, rate));
            break;
        }
        case 2:
        {
            int index;
            double payment;

            lms.displayLoans();

            if (lms.getLoansCount() == 0)
            {          // Check if there are any loans
                break; // No loans to process payments for
            }
            std::cout << "\nEnter the loan index to make a payment: ";
            std::cin >> index;

            if (index < 1 || index > lms.getLoansCount())
            { // Validate index
                std::cout << "Invalid index!\n";
                break;
            }

            std::cout << "Enter the payment amount: ";
            std::cin >> payment;

            lms.makePayment(index - 1, payment); // Adjusting for zero-based index
            break;
        }
        case 3:
            lms.displayLoans();
            break;
        case 4:
            std::cout << "Exiting the system.\n";
            break;
        default:
            std::cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
