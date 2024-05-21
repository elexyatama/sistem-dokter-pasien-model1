#include "header.h"

void displayMenu() {
    cout << "----- Menu -----\n";
    cout << "1. Insert Doctor\n";
    cout << "2. Insert Patient\n";
    cout << "3. Delete Doctor\n";
    cout << "4. Delete Patient\n";
    cout << "5. Search Doctor\n";
    cout << "6. Search Patient\n";
    cout << "7. Print All Doctors\n";
    cout << "8. Print All Doctor and Patients\n";
    cout << "9. Count Patients\n";
    cout << "10. Count Patients from a Doctor\n";
    cout << "11. Count Patients by Diagnosis\n";
    cout << "12. Count Doctors by Diagnosis\n";
    cout << "13. Move Patient\n";
    cout << "0. Exit\n";
    cout << "-----------------\n";
    cout << "Enter your choice: ";
}

int main() {
    list_doctor ld;
    create_list_doctor(ld);
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                process_insert_doctor(ld);
                break;
            case 2:
                process_insert_patient(ld);
                break;
            case 3: 
                process_delete_doctor(ld);
                break;
            case 4:
                process_delete_patient(ld);
                break;
            case 5:
                process_search_doctor(ld);
                break;
            case 6:
                process_search_patient(ld);
                break;
            case 7:
                print_all_doctor(ld);
                break;
            case 8:
                print_all_doctor_patient(ld);
                break;
            case 9:
                process_patient_count(ld);
                break;
            case 10: 
                process_patient_count_from_doctor(ld);
                break;
            case 11: 
                process_patient_diagnosis_count(ld);
                break;
            case 12:
                process_doctor_diagnosis_count(ld);
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}