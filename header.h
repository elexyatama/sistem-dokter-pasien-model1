#ifndef HEADER_DOCPAT_INCLUDED
#define HEADER_DOCPAT_INCLUDED
#include <iostream>

using namespace std;

struct infotype_doctor
{
    string name;
    string id;
    string specialist;
    int age;
};

struct infotype_patient
{
    string name;
    string id;
    string diagnosis;
    int age;
};

typedef struct elm_doctor *adr_doctor;
typedef struct elm_patient *adr_patient;

struct elm_doctor
{
    infotype_doctor info;
    adr_doctor next;
    adr_patient listPatient;
};

struct elm_patient
{
    infotype_patient info;
    adr_patient next;
    adr_patient prev;
};

struct list_doctor
{
    adr_doctor first;
};

void create_list_doctor(list_doctor &ld);

adr_doctor create_elm_doctor(infotype_doctor x);
adr_patient create_elm_patient(infotype_patient x);

void insert_doctor(list_doctor &ld, adr_doctor x);
void insert_patient(adr_doctor &ad, adr_patient x);

bool delete_doctor_id(list_doctor &ld, string id);
bool delete_patient_id(list_doctor &ld, string id);
void delete_all_patient_from_doctor_id(adr_doctor &ad);

adr_doctor search_doctor_id(list_doctor ld, string id);
adr_patient search_patient_id(list_doctor ld, string id);

void process_insert_doctor(list_doctor &ld); //a
void process_insert_patient(list_doctor &ld); //b
void process_delete_doctor(list_doctor &ld); //c
void process_delete_patient(list_doctor &ld); //d
void process_search_doctor(list_doctor ld); //e
void process_search_patient(list_doctor ld); //f

void print_all_doctor(list_doctor ld); //g
void print_doctor_data(adr_doctor ad);//h
void print_all_doctor_patient(list_doctor ld); //i
void print_patient_data(adr_patient ap); //j

int patient_count(list_doctor ld); //k
int patient_count_from_doctor(adr_doctor ad); //l
int patient_diagnosis_count(list_doctor ld, string diag); //m
int doctor_diagnosis_count(list_doctor ld, string diag); //n

void move_patient(adr_doctor &from, adr_doctor &to, adr_patient &x); //o
void process_move_patient(list_doctor &ld);

#endif