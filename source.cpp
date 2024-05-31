#include "header.h"

//ini buat create list dokter, teknis nya biasa lah ya
void create_list_doctor(list_doctor &ld) 
{
    ld.first = NULL;
}

//ini buat create elm dokter, nanti info2 terkait dg dokter disimpen ke sebuah node ato elemen
// ini fungsi buat masukin info tersebut ke dalam sebuah elemen
adr_doctor create_elm_doctor(infotype_doctor x) 
{
    adr_doctor newDoctor = new elm_doctor;
    newDoctor->info = x;
    newDoctor->next = NULL;
    newDoctor->listPatient = NULL;
    return newDoctor;
}

//sama kaya fungsi sebelumnya, bedanya ini buat client
adr_patient create_elm_patient(infotype_patient x) 
{
    adr_patient newPatient = new elm_patient;
    newPatient->info = x;
    newPatient->next = NULL;
    newPatient->prev = NULL;
    return newPatient;
}

//fungsi buat insert dokter ke dalam list, ini metode insert last
void insert_doctor(list_doctor &ld, adr_doctor x) 
{
    //kondisi ketika list kosong
    if (ld.first == NULL) {
        ld.first = x;
    } else { //kondisi normal
        adr_doctor temp = ld.first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = x;
    }
}

//fungsi buat insert patient kedalam lsit, ini metode insert last
void insert_patient(adr_doctor &ad, adr_patient x) 
{
    //kondisi ketika list kosong
    if (ad->listPatient == NULL) {
        ad->listPatient = x;
    } else { //kondisi normal
        adr_patient temp = ad->listPatient;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = x;
        x->prev = temp;
    }
}

//fungsi buat delete dokter by id
bool delete_doctor_id(list_doctor &ld, string id) {
    //ngecek apakah list kosong, kalo kosong keluar fungsi
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

// fungsi delete pasien by id
bool delete_patient_id(list_doctor &ld, string id) 
{
    //dicek dari dokter ke dokter, ini inisiasi var currdocter ke dokter awal
    adr_doctor currentDoctor = ld.first;
    
    //looping buat nyadi pasien tersebut dari beberapa list dokter
    while (currentDoctor != NULL) {
        adr_patient currentPatient = currentDoctor->listPatient;
        adr_patient previousPatient = NULL;

        //in while loop buat ngecek smua pasien yang seorang dokter punya
        while (currentPatient != NULL) {
            //kalo nemu, mulai proses delete disini
            if (currentPatient->info.id == id) {
                //kasus pasien dilist pertama
                if (previousPatient == NULL) {
                    currentDoctor->listPatient = currentPatient->next;
                } else { //kasus normal
                    previousPatient->next = currentPatient->next;
                }
                //kasus kalo pasien di list terakhir
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
    //kalo ga nemu pasiennya, return false, ini berguna difungsi lain
    return false;
}

//fungsi ini buat hapus semua pasien yang berada di seorang ddokter
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
            return current; // Mengembalikan elm ke dokter yang ditemukan
        }
        current = current->next;
    }
    return NULL; // Mengembalikan NULL kalo dokter dengan ID tersebut tidak ditemukan
}

adr_patient search_patient_id(list_doctor ld, string id, adr_doctor &doctor)
{
    adr_doctor currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        adr_patient currentPatient = currentDoctor->listPatient;
        while (currentPatient != NULL) {
            if (currentPatient->info.id == id) {
                doctor = currentDoctor; // Mengisi parameter 'doctor' dengan dokter yang ditemukan, penting buat fungsi process_search_patient
                return currentPatient; // Mengembalikan elm ke pasien yang ditemukan
            }
            currentPatient = currentPatient->next;
        }
        currentDoctor = currentDoctor->next;
    }
    doctor = NULL; // Mengatur 'doctor' ke NULL kalo pasien tidak ditemukan
    return NULL; // Mengembalikan NULL kalo pasien dengan ID tersebut tidak ditemukan
}

void process_insert_doctor(list_doctor &ld)
{
    infotype_doctor newDoctorInfo;

    // Meminta input dari pengguna untuk informasi dokter
    cout << "Enter Doctor ID: ";
    cin >> newDoctorInfo.id;
    cout << "Enter Doctor Name: "; cin.ignore(); // Mengabaikan karakter newline dari input sebelumnya, intinya ini biar getline() ga error
    getline(cin, newDoctorInfo.name); 
    cout << "Enter Doctor Specialist: ";
    getline(cin, newDoctorInfo.specialist); 
    cout << "Enter Doctor Age: ";
    cin >> newDoctorInfo.age; 

    adr_doctor newDoctor = create_elm_doctor(newDoctorInfo); // Membuat elemen dokter baru
    insert_doctor(ld, newDoctor); // Menambahkan dokter baru ke dalam daftar dokter

    cout << "Doctor added successfully.\n"; 
}


void process_insert_patient(list_doctor &ld) 
{
    string doctorID;
    cout << "Enter Doctor ID: ";
    cin >> doctorID;

    // Mencari dokter berdasarkan ID
    adr_doctor doctor = search_doctor_id(ld, doctorID);
    if (doctor == NULL) {
        // Jika dokter tidak ditemukan, tampilkan pesan dan keluar dari fungsi
        cout << "Doctor with ID " << doctorID << " not found." << endl;
        return;
    }

    infotype_patient newPatientInfo;
    // Meminta input dari pengguna untuk informasi pasien baru
    cout << "Enter Patient ID: ";
    cin >> newPatientInfo.id;
    cout << "Enter Patient Name: "; 
    cin.ignore(); // Mengabaikan karakter newline dari input sebelumnya, biar getline() ga error
    getline(cin, newPatientInfo.name); // Mengambil input nama pasien
    cout << "Enter Patient Diagnosis: ";
    getline(cin, newPatientInfo.diagnosis); // Mengambil input diagnosis pasien
    cout << "Enter Patient Age: ";
    cin >> newPatientInfo.age; // Mengambil input usia pasien

    // Membuat elemen pasien baru
    adr_patient newPatient = create_elm_patient(newPatientInfo);
    // Menambahkan pasien baru ke dalam daftar pasien dokter yang ditemukan
    insert_patient(doctor, newPatient);

    cout << "Patient added successfully to Doctor " << doctorID << "." << endl;
}

void process_delete_doctor(list_doctor &ld) 
{
    string doctorID;
    cout << "Enter Doctor ID to delete: ";
    cin >> doctorID;

    // Menghapus dokter berdasarkan ID dan semua pasien terkait
    if (delete_doctor_id(ld, doctorID)) {
        cout << "Doctor with ID " << doctorID << " and all associated patients were successfully deleted." << endl;
    } else { //kasus klo dokter ngga ditemukan
        cout << "Doctor with ID " << doctorID << " not found." << endl;
    }
}


void process_delete_patient(list_doctor &ld) 
{
    string patientID;
    cout << "Enter Patient ID to delete: ";
    cin >> patientID;

    // Menghapus pasien berdasarkan ID
    if (delete_patient_id(ld, patientID)) {
        // kasus pasien berhasil dihapus, tampilkan pesan
        cout << "Patient with ID " << patientID << " was successfully deleted." << endl;
    } else {
        // kasus pasien tidak ditemukan, tampilkan pesan
        cout << "Patient with ID " << patientID << " not found." << endl;
    }
}

void process_search_doctor(list_doctor ld) 
{
    string doctorID;
    cout << "Enter Doctor ID to search: ";
    cin >> doctorID;

    // Mencari dokter berdasarkan ID
    adr_doctor doctor = search_doctor_id(ld, doctorID);
    if (doctor != NULL) {
        // kasus dokter ditemukan, cetak data dokter
        print_doctor_data(doctor);
    } else {
        // kasus dokter tidak ditemukan, tampilkan pesan
        cout << "Doctor with ID " << doctorID << " not found." << endl;
    }
}

void process_search_patient(list_doctor ld) 
{
    string patientID;
    cout << "Enter Patient ID to search: ";
    cin >> patientID;

    adr_doctor doctor = NULL;
    // Mencari pasien berdasarkan ID dan juga mengisi dokter yang menangani
    adr_patient patient = search_patient_id(ld, patientID, doctor);

    if (patient != NULL && doctor != NULL) {
        // Jika pasien ditemukan, cetak data pasien
        print_patient_data(patient);
        // Cetak juga informasi dokter yang menangani pasien tersebut
        cout << "Assigned Doctor:" << endl;
        cout << "-------------------------------" << endl;
        cout << "Doctor ID: " << doctor->info.id << endl;
        cout << "Doctor Name: " << doctor->info.name << endl;
        cout << "-------------------------------" << endl;
    } else {
        // Jika pasien tidak ditemukan, tampilkan pesan
        cout << "Patient with ID " << patientID << " not found." << endl;
    }  

    // Menunggu pengguna menekan Enter sebelum melanjutkan, biar bisa lihat data pasiennya dulu
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
    int count = 0; // Inisialisasi penghitung pasien dengan nilai awal 0
    adr_doctor currentDoctor = ld.first; // Pointer untuk dokter saat ini, mulai dari dokter pertama dalam daftar
    while (currentDoctor != NULL) { // Iterasi selama masih ada dokter dalam daftar
        adr_patient currentPatient = currentDoctor->listPatient; // Pointer untuk pasien saat ini, mulai dari pasien pertama dari dokter saat ini
        while (currentPatient != NULL) { // Iterasi selama masih ada pasien dalam daftar pasien dokter saat ini
            count++; // Tambahkan penghitung setiap kali ditemukan pasien
            currentPatient = currentPatient->next; // Pindah ke pasien berikutnya dalam daftar pasien dokter saat ini
        }
        currentDoctor = currentDoctor->next; // Pindah ke dokter berikutnya dalam daftar
    }
    return count; // Kembalikan jumlah total pasien dari semua dokter dalam daftar
}

int patient_count_from_doctor(adr_doctor ad) 
{
    int count = 0; // Inisialisasi penghitung pasien
    adr_patient currentPatient = ad->listPatient; // Pointer untuk pasien saat ini
    while (currentPatient != NULL) { // Iterasi selama masih ada pasien
        count++; // Tambahkan penghitung pasien
        currentPatient = currentPatient->next; // Pindah ke pasien berikutnya
    }
    return count; // Kembalikan jumlah total pasien
}

int patient_diagnosis_count(list_doctor ld, string diag) 
{
    int count = 0; // Inisialisasi penghitung pasien dengan diagnosis tertentu
    adr_doctor currentDoctor = ld.first; // Pointer untuk dokter saat ini
    while (currentDoctor != NULL) { // Iterasi selama masih ada dokter
        adr_patient currentPatient = currentDoctor->listPatient; // Pointer untuk pasien saat ini
        while (currentPatient != NULL) { // Iterasi selama masih ada pasien
            if (currentPatient->info.diagnosis == diag) { // Jika diagnosis pasien cocok
                count++; // Tambahkan penghitung pasien
            }
            currentPatient = currentPatient->next; // Pindah ke pasien berikutnya
        }
        currentDoctor = currentDoctor->next; // Pindah ke dokter berikutnya
    }
    return count; // Kembalikan jumlah total pasien dengan diagnosis tertentu
}

int doctor_diagnosis_count(list_doctor ld, string diag) 
{
    int count = 0; // Inisialisasi penghitung dokter
    adr_doctor currentDoctor = ld.first; // Pointer untuk dokter saat ini
    while (currentDoctor != NULL) { // Iterasi selama masih ada dokter
        adr_patient currentPatient = currentDoctor->listPatient; // Pointer untuk pasien saat ini
        while (currentPatient != NULL) { // Iterasi selama masih ada pasien
            if (currentPatient->info.diagnosis == diag) { // Jika diagnosis pasien cocok
                count++; // Tambahkan penghitung dokter
                break; // Keluar dari loop pasien untuk menghindari penghitungan ganda
            }
            currentPatient = currentPatient->next; // Pindah ke pasien berikutnya
        }
        currentDoctor = currentDoctor->next; // Pindah ke dokter berikutnya
    }
    return count; // Kembalikan jumlah total dokter yang menangani pasien dengan diagnosis tertentu
}


void move_patient(adr_doctor &from, adr_doctor &to, adr_patient &x) {
    if (from != NULL && x != NULL) {
        adr_patient currentPatient = from->listPatient;
        adr_patient previousPatient = NULL;

        // Mencari pasien dalam daftar pasien dari dokter asal
        while (currentPatient != NULL && currentPatient != x) {
            previousPatient = currentPatient;
            currentPatient = currentPatient->next;
        }

        // Jika pasien ditemukan, lepaskan dari daftar pasien dokter asal
        if (currentPatient == x) {
            if (previousPatient != NULL) {
                previousPatient->next = currentPatient->next;
            } else {
                from->listPatient = currentPatient->next;
            }
            currentPatient->next = NULL; // Putuskan hubungan pasien dari daftar lama
        }
    }

    // Tambahkan pasien ke daftar pasien dari dokter tujuan
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

    // Mencari pasien dalam seluruh daftar dokter
    adr_doctor currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        adr_patient currentPatient = currentDoctor->listPatient;
        while (currentPatient != NULL) {
            if (currentPatient->info.id == patientID) {
                patientToMove = currentPatient;
                fromDoctor = currentDoctor;
                break; // Pasien ditemukan, keluar dari loop
            }
            currentPatient = currentPatient->next;
        }
        if (patientToMove != NULL) {
            break; // Pasien ditemukan, keluar dari loop dokter
        }
        currentDoctor = currentDoctor->next;
    }

    // Jika pasien ditemukan, cetak data pasien
    if (patientToMove != NULL) {
        print_patient_data(patientToMove);
    } else {
        cout << "Patient with ID " << patientID << " not found." << endl;
        return;
    }

    // Meminta ID dokter tujuan dari pengguna
    cout << "Enter Doctor ID to move the patient to: ";
    cin >> toDoctorID;

    // Mencari dokter tujuan berdasarkan ID
    currentDoctor = ld.first;
    while (currentDoctor != NULL) {
        if (currentDoctor->info.id == toDoctorID) {
            toDoctor = currentDoctor;
            break; // Dokter tujuan ditemukan, keluar dari loop
        }
        currentDoctor = currentDoctor->next;
    }

    // Jika dokter tujuan tidak ditemukan, cetak pesan kesalahan
    if (toDoctor == NULL) {
        cout << "Doctor with ID " << toDoctorID << " not found." << endl;
        return;
    }

    // Pindahkan pasien dari dokter asal ke dokter tujuan
    move_patient(fromDoctor, toDoctor, patientToMove);
    cout << "Patient with ID " << patientID << " successfully moved to Doctor with ID " << toDoctorID << "." << endl;
}



