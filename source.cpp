#include "header.h"

void create_list_doctor(list_doctor &ld)
{
    ld.first = NULL;
}

adr_doctor create_elm_doctor(infotype_doctor x) 
{
    adr_doctor newDoctor = new elm_doctor;
    newDoctor->info = x;
    newDoctor->next = NULL;
    newDoctor->listPatient = NULL;
    return newDoctor;
}


adr_patient create_elm_patient(infotype_patient x) 
{
    adr_patient newPatient = new elm_patient;
    newPatient->info = x;
    newPatient->next = NULL;
    newPatient->prev = NULL;
    return newPatient;
}


void insert_doctor(list_doctor &ld, adr_doctor x) 
{
    if (ld.first == NULL) {
        ld.first = x;
    } else {
        adr_doctor temp = ld.first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = x;
    }
}


void insert_patient(adr_doctor &ad, adr_patient x) 
{
    if (ad->listPatient == NULL) {
        ad->listPatient = x;
    } else {
        adr_patient temp = ad->listPatient;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = x;
        x->prev = temp;
    }
}

bool delete_doctor_id(list_doctor &ld, string id) {
    if (ld.first == NULL) {
        return false;
    }
    adr_doctor current = ld.first;
    adr_doctor previous = NULL;

    // nyari dokter dg id tersebut
    while (current != NULL && current->info.id != id) {
        previous = current;
        current = current->next;
    }

    // kasus ketika sampe ujung list tapi dokter gada, return false
    if (current == NULL) {
        return false;
    }

    // kasus ketika dokter first element
    if (current == ld.first) {
        ld.first = current->next;
    } else {
        previous->next = current->next;
    }

    // hapus pasien dari dokter yang mau dihapus
    delete_all_patient_from_doctor_id(current);

    // delete node ato element dokter tsb
    delete current;
    return true;
}


bool delete_patient_id(list_doctor &ld, string id) 
{
    adr_doctor currentDoctor = ld.first;
    
    while (currentDoctor != NULL) {
        adr_patient currentPatient = currentDoctor->listPatient;
        adr_patient previousPatient = NULL;

        while (currentPatient != NULL) {
            if (currentPatient->info.id == id) {
                if (previousPatient == NULL) {
                    currentDoctor->listPatient = currentPatient->next;
                } else {
                    previousPatient->next = currentPatient->next;
                }

                if (currentPatient->next != NULL) {
                    currentPatient->next->prev = previousPatient;
                }

                delete currentPatient;
                return true;
            }

            previousPatient = currentPatient;
            currentPatient = currentPatient->next;
        }

        currentDoctor = currentDoctor->next;
    }
    
    return false;
}


void delete_all_patient_from_doctor_id(adr_doctor &ad) 
{
    adr_patient current = ad->listPatient;
    while (current != NULL) {
        adr_patient toDelete = current;
        current = current->next;
        delete toDelete;
    }
    ad->listPatient = NULL;
}


adr_doctor search_doctor_id(list_doctor ld, string id) 
{
    adr_doctor current = ld.first;
    while (current != NULL) {
        if (current->info.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

adr_patient search_patient_id(list_doctor ld, string id, adr_doctor &doctor)
{
    adr_doctor currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        adr_patient currentPatient = currentDoctor->listPatient;
        while (currentPatient != NULL) {
            if (currentPatient->info.id == id) {
                doctor = currentDoctor; 
                return currentPatient; 
            }
            currentPatient = currentPatient->next;
        }
        currentDoctor = currentDoctor->next;
    }
    doctor = NULL; 
    return NULL; 
}


void process_insert_doctor(list_doctor &ld)
{
    infotype_doctor newDoctorInfo;

    cout << "Enter Doctor ID: ";
    cin >> newDoctorInfo.id;
    cout << "Enter Doctor Name: "; cin.ignore(); 
    getline(cin, newDoctorInfo.name);
    cout << "Enter Doctor Specialist: ";
    getline(cin, newDoctorInfo.specialist);
    cout << "Enter Doctor Age: ";
    cin >> newDoctorInfo.age;

    adr_doctor newDoctor = create_elm_doctor(newDoctorInfo);
    insert_doctor(ld, newDoctor);

    cout << "Doctor added successfully.\n";
} 

void process_insert_patient(list_doctor &ld) 
{
    string doctorID;
    cout << "Enter Doctor ID: ";
    cin >> doctorID;

    adr_doctor doctor = search_doctor_id(ld, doctorID);
    if (doctor == NULL) {
        cout << "Doctor with ID " << doctorID << " not found." << endl;
        return;
    }

    infotype_patient newPatientInfo;
    cout << "Enter Patient ID: ";
    cin >> newPatientInfo.id;
    cout << "Enter Patient Name: "; cin.ignore(); 
    getline(cin, newPatientInfo.name);
    cout << "Enter Patient Diagnosis: ";
    getline(cin, newPatientInfo.diagnosis);
    cout << "Enter Patient Age: ";
    cin >> newPatientInfo.age;

    adr_patient newPatient = create_elm_patient(newPatientInfo);
    insert_patient(doctor, newPatient);

    cout << "Patient added successfully to Doctor " << doctorID << "." << endl;
}

void process_delete_doctor(list_doctor &ld) 
{
    string doctorID;
    cout << "Enter Doctor ID to delete: ";
    cin >> doctorID;

    if (delete_doctor_id(ld, doctorID)) {
        cout << "Doctor with ID " << doctorID << " and all associated patients were successfully deleted." << endl;
    } else {
        cout << "Doctor with ID " << doctorID << " not found." << endl;
    }
}

void process_delete_patient(list_doctor &ld) 
{
    string patientID;
    cout << "Enter Patient ID to delete: ";
    cin >> patientID;

    if (delete_patient_id(ld, patientID)) {
        cout << "Patient with ID " << patientID << " was successfully deleted." << endl;
    } else {
        cout << "Patient with ID " << patientID << " not found." << endl;
    }
}

void process_search_doctor(list_doctor ld) 
{
    string doctorID;
    cout << "Enter Doctor ID to search: ";
    cin >> doctorID;

    adr_doctor doctor = search_doctor_id(ld, doctorID);
    if (doctor != NULL) {
        print_doctor_data(doctor);
    } else {
        cout << "Doctor with ID " << doctorID << " not found." << endl;
    }
}

void process_search_patient(list_doctor ld) 
{
    string patientID;
    cout << "Enter Patient ID to search: ";
    cin >> patientID;

    adr_doctor doctor = NULL;
    adr_patient patient = search_patient_id(ld, patientID, doctor);

    if (patient != NULL && doctor != NULL) {
        print_patient_data(patient);
        cout << "Assigned Doctor:" << endl;
        cout << "-------------------------------" << endl;
        cout << "Doctor ID: " << doctor->info.id << endl;
        cout << "Doctor Name: " << doctor->info.name << endl;
        cout << "-------------------------------" << endl;
    } else {
        cout << "Patient with ID " << patientID << " not found." << endl;
    }  
    cout << "Press Enter to continue...";
    cin.ignore(); 
    cin.get(); 
}


void print_all_doctor(list_doctor ld) 
{
    cout << "---------------------------------" << endl;
    cout << "List of All Doctors" << endl;
    cout << "---------------------------------" << endl;
    adr_doctor currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        cout << "Doctor ID: " << currentDoctor->info.id << endl;
        cout << "Doctor Name: " << currentDoctor->info.name << endl;
        cout << "Doctor Specialist: " << currentDoctor->info.specialist << endl;
        cout << "Doctor Age: " << currentDoctor->info.age << endl;
        cout << "---------------------------------" << endl;
        currentDoctor = currentDoctor->next;
    }
    cout << "Press Enter to continue...";
    cin.ignore(); 
    cin.get();   
}

void print_all_doctor_patient(list_doctor ld) 
{
    cout << "---------------------------------" << endl;
    cout << "List of All Doctors with Patients" << endl;
    cout << "---------------------------------" << endl;
    adr_doctor currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        cout << "Doctor ID: " << currentDoctor->info.id << endl;
        cout << "Doctor Name: " << currentDoctor->info.name << endl;
        cout << "Doctor Specialist: " << currentDoctor->info.specialist << endl;
        cout << "Doctor Age: " << currentDoctor->info.age << endl;
        cout << "Patients:" << endl;
        if (currentDoctor->listPatient != NULL) {
            adr_patient currentPatient = currentDoctor->listPatient;
            while (currentPatient != NULL) {
                cout << "  Patient ID: " << currentPatient->info.id << endl;
                cout << "  Patient Name: " << currentPatient->info.name << endl;
                cout << "  Patient Diagnosis: " << currentPatient->info.diagnosis << endl;
                cout << "  Patient Age: " << currentPatient->info.age << endl;
                cout << "---------------------------------" << endl;
                currentPatient = currentPatient->next;
            }
        } else {
            cout << "  No patients assigned to this doctor." << endl;
            cout << "---------------------------------" << endl;
        }
        currentDoctor = currentDoctor->next;
    }
    cout << "Press Enter to continue...";
    cin.ignore(); 
    cin.get();  
}

void print_patient_data(adr_patient ap) 
{
    if (ap != NULL) {
        cout << "-------------------------------" << endl;
        cout << "Patient ID: " << ap->info.id << endl;
        cout << "Patient Name: " << ap->info.name << endl;
        cout << "Patient Diagnosis: " << ap->info.diagnosis << endl;
        cout << "Patient Age: " << ap->info.age << endl;
        cout << "-------------------------------" << endl;
    } else {
        cout << "Patient data is null." << endl;
    }
}

void print_doctor_data(adr_doctor ad) {
    if (ad != NULL) {
        cout << "===============================" << endl;
        cout << "Doctor ID: " << ad->info.id << endl;
        cout << "Doctor Name: " << ad->info.name << endl;
        cout << "Doctor Specialist: " << ad->info.specialist << endl;
        cout << "Doctor Age: " << ad->info.age << endl;
        cout << "===============================" << endl;
        cout << "Patients:" << endl;
        if (ad->listPatient != NULL) {
            adr_patient currentPatient = ad->listPatient;
            while (currentPatient != NULL) {
                print_patient_data(currentPatient);
                currentPatient = currentPatient->next;
            }
        } else {
            cout << "No patients assigned to this doctor." << endl;
        }
        cout << "===============================" << endl;
    } else {
        cout << "Doctor data is null." << endl;
    }
    cout << "Press Enter to continue...";
    cin.ignore(); 
    cin.get();  
}

void process_patient_count(list_doctor ld) 
{
    int count = patient_count(ld);
    cout << "Total number of patients: " << count << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void process_patient_count_from_doctor(list_doctor ld) 
{
    string doctorID;
    cout << "Enter Doctor ID: ";
    cin >> doctorID;

    adr_doctor doctor = search_doctor_id(ld, doctorID);
    if (doctor != NULL) {
        int count = patient_count_from_doctor(doctor);
        cout << "Number of patients for Doctor ID " << doctorID << ": " << count << endl;
    } else {
        cout << "Doctor with ID " << doctorID << " not found." << endl;
    }
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void process_patient_diagnosis_count(list_doctor ld) 
{
    string diagnosis;
    cout << "Enter Diagnosis: ";
    cin >> diagnosis;

    int count = patient_diagnosis_count(ld, diagnosis);
    cout << "Number of patients with diagnosis '" << diagnosis << "': " << count << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void process_doctor_diagnosis_count(list_doctor ld) 
{
    string diagnosis;
    cout << "Enter Diagnosis: ";
    cin >> diagnosis;

    int count = doctor_diagnosis_count(ld, diagnosis);
    cout << "Number of doctors encountering patients with diagnosis '" << diagnosis << "': " << count << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

int patient_count(list_doctor ld) 
{
    int count = 0;
    adr_doctor currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        adr_patient currentPatient = currentDoctor->listPatient;
        while (currentPatient != NULL) {
            count++;
            currentPatient = currentPatient->next;
        }
        currentDoctor = currentDoctor->next;
    }
    return count;
}

int patient_count_from_doctor(adr_doctor ad) 
{
    int count = 0;
    adr_patient currentPatient = ad->listPatient;
    while (currentPatient != NULL) {
        count++;
        currentPatient = currentPatient->next;
    }
    return count;
}

int patient_diagnosis_count(list_doctor ld, string diag) 
{
    int count = 0;
    adr_doctor currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        adr_patient currentPatient = currentDoctor->listPatient;
        while (currentPatient != NULL) {
            if (currentPatient->info.diagnosis == diag) {
                count++;
            }
            currentPatient = currentPatient->next;
        }
        currentDoctor = currentDoctor->next;
    }
    return count;
}


int doctor_diagnosis_count(list_doctor ld, string diag) 
{
    int count = 0;
    adr_doctor currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        adr_patient currentPatient = currentDoctor->listPatient;
        while (currentPatient != NULL) {
            if (currentPatient->info.diagnosis == diag) {
                count++;
                break; // Count the doctor only once per diagnosis
            }
            currentPatient = currentPatient->next;
        }
        currentDoctor = currentDoctor->next;
    }
    return count;
}

void move_patient(adr_doctor &from, adr_doctor &to, adr_patient &x) {
    // Remove patient from 'from' doctor
    if (from != NULL && x != NULL) {
        adr_patient currentPatient = from->listPatient;
        adr_patient previousPatient = NULL;
        while (currentPatient != NULL && currentPatient != x) {
            previousPatient = currentPatient;
            currentPatient = currentPatient->next;
        }
        if (currentPatient == x) {
            if (previousPatient != NULL) {
                previousPatient->next = currentPatient->next;
            } else {
                from->listPatient = currentPatient->next;
            }
            currentPatient->next = NULL;
        }
    }

    // Add patient to 'to' doctor
    if (to != NULL && x != NULL) {
        x->next = to->listPatient;
        to->listPatient = x;
    }
}


void process_move_patient(list_doctor &ld) {
    string patientID, fromDoctorID, toDoctorID;
    cout << "Enter Patient ID to move: ";
    cin >> patientID;

    adr_patient patientToMove = NULL;
    adr_doctor fromDoctor = NULL, toDoctor = NULL;

    adr_doctor currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        adr_patient currentPatient = currentDoctor->listPatient;
        while (currentPatient != NULL) {
            if (currentPatient->info.id == patientID) {
                patientToMove = currentPatient;
                fromDoctor = currentDoctor;
                break;
            }
            currentPatient = currentPatient->next;
        }
        if (patientToMove != NULL) {
            break;
        }
        currentDoctor = currentDoctor->next;
    }

    if (patientToMove != NULL) {
        print_patient_data(patientToMove);
    } else {
        cout << "Patient with ID " << patientID << " not found." << endl;
        return;
    }

    cout << "Enter Doctor ID to move the patient to: ";
    cin >> toDoctorID;

    currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        if (currentDoctor->info.id == toDoctorID) {
            toDoctor = currentDoctor;
            break;
        }
        currentDoctor = currentDoctor->next;
    }

    if (toDoctor == NULL) {
        cout << "Doctor with ID " << toDoctorID << " not found." << endl;
        return;
    }

    move_patient(fromDoctor, toDoctor, patientToMove);
    cout << "Patient with ID " << patientID << " successfully moved to Doctor with ID " << toDoctorID << "." << endl;
}


