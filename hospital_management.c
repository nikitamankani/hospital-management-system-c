#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100
#define MAX_ROOMS 20
#define MAX_MEDICINES 50
#define DATE_SIZE 11
#define TIME_SIZE 6
#define NAME_SIZE 50
#define MEDICINE_NAME_SIZE 50

typedef struct {
    int id;
    char name[NAME_SIZE];
    int age;
    char gender;
    char diagnosis[100];
} Patient;

typedef struct {
    int id;
    int patient_id;
    char date[DATE_SIZE];
    char time[TIME_SIZE];
    char doctor_name[NAME_SIZE];
} Appointment;

typedef struct {
    int room_number;
    int is_available;
    int occupied_by_patient_id;
} Room;

typedef struct {
    int medicine_id;
    char medicine_name[MEDICINE_NAME_SIZE];
    int quantity;
} Medicine;

Patient patients[MAX_PATIENTS];
Appointment appointments[MAX_APPOINTMENTS];
Room rooms[MAX_ROOMS];
Medicine medicines[MAX_MEDICINES];

int patient_count = 0;
int appointment_count = 0;
int medicine_count = 0;

const char *patients_file = "patients.dat";
const char *appointments_file = "appointments.dat";
const char *medicines_file = "medicines.dat";
const char *rooms_file = "rooms.dat";

void addPatient();
void viewPatients();
void editPatient();
void searchPatients();
void addAppointment();
void viewAppointments();
void cancelAppointment();
void checkRoomAvailability();
void addMedicine();
void viewMedicines();
void dispenseMedicine();
void occupyRoom();
void vacateRoom();

void loadData();
void saveData();

int main() {
    loadData();

    int choice;
    do {
        printf("\nHospital Management System\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Edit Patient Information\n");
        printf("4. Search Patients\n");
        printf("5. Add Appointment\n");
        printf("6. View Appointments\n");
        printf("7. Cancel Appointment\n");
        printf("8. Check Room Availability\n");
        printf("9. Add Medicine\n");
        printf("10. View Medicines\n");
        printf("11. Dispense Medicine\n");
        printf("12. Occupy Room\n");
        printf("13. Vacate Room\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                editPatient();
                break;
            case 4:
                searchPatients();
                break;
            case 5:
                addAppointment();
                break;
            case 6:
                viewAppointments();
                break;
            case 7:
                cancelAppointment();
                break;
            case 8:
                checkRoomAvailability();
                break;
            case 9:
                addMedicine();
                break;
            case 10:
                viewMedicines();
                break;
            case 11:
                dispenseMedicine();
                break;
            case 12:
                occupyRoom();
                break;
            case 13:
                vacateRoom();
                break;
            case 0:
                printf("Exiting and saving data...\n");
                saveData();
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

void addPatient() {
    if (patient_count < MAX_PATIENTS) {
        Patient newPatient;
        newPatient.id = patient_count + 1;
        printf("Enter patient name: ");
        if (scanf(" %[^n]s", newPatient.name) != 1) return;
        printf("Enter patient age: ");
        if (scanf("%d", &newPatient.age) != 1) { while(getchar() != '\n'); return; }
        printf("Enter patient gender (M/F/O): ");
        if (scanf(" %c", &newPatient.gender) != 1) { while(getchar() != '\n'); return; }
        printf("Enter patient diagnosis: ");
        if (scanf(" %[^n]s", newPatient.diagnosis) != 1) return;

        patients[patient_count++] = newPatient;
        printf("Patient added successfully!\n");
    } else {
        printf("Maximum patient limit reached!\n");
    }
}

void viewPatients() {
    if (patient_count == 0) {
        printf("No patients found.\n");
        return;
    }
    printf("\nPatient List:\n");
    printf("ID\tName\tAge\tGender\tDiagnosis\n");
    for (int i = 0; i < patient_count; i++) {
        printf("%d\t%s\t%d\t%c\t%s\n", patients[i].id, patients[i].name, patients[i].age, patients[i].gender, patients[i].diagnosis);
    }
}

void editPatient() {
    int patientId;
    printf("Enter the ID of the patient to edit: ");
    if (scanf("%d", &patientId) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while(getchar() != '\n');
        return;
    }

    int found = 0;
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].id == patientId) {
            printf("Patient found. Enter new details:\n");
            printf("Enter new name (%s): ", patients[i].name);
            if (scanf(" %[^n]s", patients[i].name) != 1) return;
            printf("Enter new age (%d): ", patients[i].age);
            if (scanf("%d", &patients[i].age) != 1) { while(getchar() != '\n'); return; }
            printf("Enter new gender (M/F/O) (%c): ", patients[i].gender);
            if (scanf(" %c", &patients[i].gender) != 1) { while(getchar() != '\n'); return; }
            printf("Enter new diagnosis (%s): ", patients[i].diagnosis);
            if (scanf(" %[^n]s", patients[i].diagnosis) != 1) return;
            printf("Patient information updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Patient with ID %d not found.\n", patientId);
    }
}

void searchPatients() {
    int searchChoice;
    printf("Search patient by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    if (scanf("%d", &searchChoice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while(getchar() != '\n');
        return;
    }

    int found = 0;
    if (searchChoice == 1) {
        int patientId;
        printf("Enter patient ID to search: ");
        if (scanf("%d", &patientId) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            return;
        }
        for (int i = 0; i < patient_count; i++) {
            if (patients[i].id == patientId) {
                printf("\nPatient Found:\n");
                printf("ID\tName\tAge\tGender\tDiagnosis\n");
                printf("%d\t%s\t%d\t%c\t%s\n", patients[i].id, patients[i].name, patients[i].age, patients[i].gender, patients[i].diagnosis);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Patient with ID %d not found.\n", patientId);
        }
    } else if (searchChoice == 2) {
        char searchName[NAME_SIZE];
        printf("Enter patient name to search: ");
        if (scanf(" %[^n]s", searchName) != 1) return;
        printf("\nMatching Patients:\n");
        printf("ID\tName\tAge\tGender\tDiagnosis\n");
        for (int i = 0; i < patient_count; i++) {
            if (strstr(patients[i].name, searchName) != NULL) {
                printf("%d\t%s\t%d\t%c\t%s\n", patients[i].id, patients[i].name, patients[i].age, patients[i].gender, patients[i].diagnosis);
                found = 1;
            }
        }
        if (!found) {
            printf("No patients found with name containing '%s'.\n", searchName);
        }
    } else {
        printf("Invalid search choice.\n");
    }
}

void addAppointment() {
    if (appointment_count < MAX_APPOINTMENTS && patient_count > 0) {
        Appointment newAppointment;
        newAppointment.id = appointment_count + 1;
        printf("Enter patient ID: ");
        if (scanf("%d", &newAppointment.patient_id) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            return;
        }

        int patientFound = 0;
        for (int i = 0; i < patient_count; i++) {
            if (patients[i].id == newAppointment.patient_id) {
                patientFound = 1;
                break;
            }
        }
        if (!patientFound) {
            printf("Patient ID not found!\n");
            return;
        }

        printf("Enter appointment date (YYYY-MM-DD): ");
        if (scanf(" %s", newAppointment.date) != 1) return;
        printf("Enter appointment time (HH:MM): ");
        if (scanf(" %s", newAppointment.time) != 1) return;
        
        // Display doctor options
        printf("\nAvailable Doctors:\n");
        printf("1. Dr. Smith (General Physician)\n");
        printf("2. Dr. Jones (Pediatrician)\n");
        printf("3. Dr. Williams (Cardiologist)\n");
        printf("4. Other (Enter name manually)\n");
        printf("Select a doctor by number, or 4 to enter manually: ");
        
        int doctorChoice;
        if (scanf("%d", &doctorChoice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            return;
        }

        switch (doctorChoice) {
            case 1:
                strcpy(newAppointment.doctor_name, "Dr. Smith");
                break;
            case 2:
                strcpy(newAppointment.doctor_name, "Dr. Jones");
                break;
            case 3:
                strcpy(newAppointment.doctor_name, "Dr. Williams");
                break;
            case 4:
                printf("Enter doctor's name: ");
                if (scanf(" %[^n]s", newAppointment.doctor_name) != 1) return;
                break;
            default:
                printf("Invalid doctor choice. Please try again.\n");
                return; 
        }

        appointments[appointment_count++] = newAppointment;
        printf("Appointment added successfully!\n");
    } else {
        printf("Maximum appointment limit reached or no patients exist.\n");
    }
}

void viewAppointments() {
    if (appointment_count == 0) {
        printf("No appointments found.\n");
        return;
    }
    printf("\nAppointment List:\n");
    printf("ID\tPatient ID\tDate        \tTime    \tDoctor Name\n");
    for (int i = 0; i < appointment_count; i++) {
        printf("%d\t%d\t\t%s\t%s\t%s\n", appointments[i].id, appointments[i].patient_id, appointments[i].date, appointments[i].time, appointments[i].doctor_name);
    }
}

void cancelAppointment() {
    int appointmentId;
    printf("Enter the ID of the appointment to cancel: ");
    if (scanf("%d", &appointmentId) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while(getchar() != '\n');
        return;
    }

    int found = 0;
    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].id == appointmentId) {
            for (int j = i; j < appointment_count - 1; j++) {
                appointments[j] = appointments[j + 1];
            }
            appointment_count--;
            printf("Appointment with ID %d cancelled successfully.\n", appointmentId);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Appointment with ID %d not found.\n", appointmentId);
    }
}

void checkRoomAvailability() {
    printf("\nRoom Availability:\n");
    printf("Room\tStatus\tPatient Details\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("%d\t%s\t", rooms[i].room_number, rooms[i].is_available ? "Available" : "Occupied");
        if (!rooms[i].is_available) {
            int patient_found = 0;
            for (int j = 0; j < patient_count; j++) {
                if (patients[j].id == rooms[i].occupied_by_patient_id) {
                    printf("ID: %d, Name: %s, Age: %d\n", patients[j].id, patients[j].name, patients[j].age);
                    patient_found = 1;
                    break;
                }
            }
            if (!patient_found) {
                printf("Patient ID: %d\n", rooms[i].occupied_by_patient_id);
            }
        } else {
            printf("-\n");
        }
    }
}

void addMedicine() {
    if (medicine_count < MAX_MEDICINES) {
        Medicine newMedicine;
        newMedicine.medicine_id = medicine_count + 1;
        printf("Enter medicine name: ");
        if (scanf(" %[^n]s", newMedicine.medicine_name) != 1) return;
        printf("Enter medicine quantity: ");
        if (scanf("%d", &newMedicine.quantity) != 1) { while(getchar() != '\n'); return; }

        medicines[medicine_count++] = newMedicine;
        printf("Medicine added successfully!\n");
    } else {
        printf("Maximum medicine limit reached.\n");
    }
}

void viewMedicines() {
    if (medicine_count == 0) {
        printf("No medicines found.\n");
        return;
    }
    printf("\nMedicine List:\n");
    printf("ID\tName\tQuantity\n");
    for (int i = 0; i < medicine_count; i++) {
        printf("%d\t%s\t%d\n", medicines[i].medicine_id, medicines[i].medicine_name, medicines[i].quantity);
    }
}

void dispenseMedicine() {
    int medicineId, quantity;
    printf("Enter medicine ID: ");
    if (scanf("%d", &medicineId) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while(getchar() != '\n');
        return;
    }
    printf("Enter quantity to dispense: ");
    if (scanf("%d", &quantity) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while(getchar() != '\n');
        return;
    }

    for (int i = 0; i < medicine_count; i++) {
        if (medicines[i].medicine_id == medicineId) {
            if (medicines[i].quantity >= quantity) {
                medicines[i].quantity -= quantity;
                printf("Dispensed %d %s.\n", quantity, medicines[i].medicine_name);
                return;
            } else {
                printf("Insufficient quantity.\n");
                return;
            }
        }
    }
    printf("Medicine not found.\n");
}

void occupyRoom() {
    int roomNumber;
    printf("Enter room number to occupy: ");
    if (scanf("%d", &roomNumber) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while(getchar() != '\n');
        return;
    }

    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        if (rooms[roomNumber - 1].is_available) {
            int patientId;
            printf("Enter patient ID: ");
            if (scanf("%d", &patientId) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while(getchar() != '\n');
                return;
            }

            int patientFound = 0;
            for (int i = 0; i < patient_count; i++) {
                if (patients[i].id == patientId) {
                    patientFound = 1;
                    break;
                }
            }
            if (!patientFound) {
                printf("Patient with ID %d not found.\n", patientId);
                return;
            }
            rooms[roomNumber - 1].is_available = 0;
            rooms[roomNumber - 1].occupied_by_patient_id = patientId;
            printf("Room %d occupied successfully by patient ID %d.\n", roomNumber, patientId);
        } else {
            printf("Room %d is already occupied.\n", roomNumber);
        }
    } else {
        printf("Invalid room number.\n");
    }
}

void vacateRoom() {
    int roomNumber;
    printf("Enter room number to vacate: ");
    if (scanf("%d", &roomNumber) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while(getchar() != '\n');
        return;
    }

    if (roomNumber > 0 && roomNumber <= MAX_ROOMS) {
        if (!rooms[roomNumber - 1].is_available) {
            int patientId = rooms[roomNumber - 1].occupied_by_patient_id;
            int patientFound = 0;
            for (int i = 0; i < patient_count; i++) {
                if (patients[i].id == patientId) {
                    patientFound = 1;
                    break;
                }
            }
            if (!patientFound) {
                printf("Patient with ID %d not found.\n", patientId);
                return;
            }
            rooms[roomNumber - 1].is_available = 1;
            rooms[roomNumber - 1].occupied_by_patient_id = 0;
            printf("Room %d vacated successfully. Patient ID %d was removed from the room.\n", roomNumber, patientId);
        } else {
            printf("Room %d is already available.\n", roomNumber);
        }
    } else {
        printf("Invalid room number.\n");
    }
}

void loadData() {
    FILE *patients_file_ptr = fopen(patients_file, "rb");
    if (patients_file_ptr) {
        fread(&patient_count, sizeof(int), 1, patients_file_ptr);
        fread(patients, sizeof(Patient), patient_count, patients_file_ptr);
        fclose(patients_file_ptr);
        printf("Patient data loaded.\n");
    } else {
        printf("No patient data found.\n");
    }

    FILE *appointments_file_ptr = fopen(appointments_file, "rb");
    if (appointments_file_ptr) {
        fread(&appointment_count, sizeof(int), 1, appointments_file_ptr);
        fread(appointments, sizeof(Appointment), appointment_count, appointments_file_ptr);
        fclose(appointments_file_ptr);
        printf("Appointment data loaded.\n");
    } else {
        printf("No appointment data found.\n");
    }

    FILE *medicines_file_ptr = fopen(medicines_file, "rb");
    if (medicines_file_ptr) {
        fread(&medicine_count, sizeof(int), 1, medicines_file_ptr);
        fread(medicines, sizeof(Medicine), medicine_count, medicines_file_ptr);
        fclose(medicines_file_ptr);
        printf("Medicine data loaded.\n");
    } else {
        printf("No medicine data found.\n");
    }

    FILE *rooms_file_ptr = fopen(rooms_file, "rb");
    if (rooms_file_ptr) {
        fread(rooms, sizeof(Room), MAX_ROOMS, rooms_file_ptr);
        fclose(rooms_file_ptr);
        printf("Room data loaded.\n");
    } else {
        for (int i = 0; i < MAX_ROOMS; i++) {
            rooms[i].room_number = i + 1;
            rooms[i].is_available = 1;
            rooms[i].occupied_by_patient_id = 0;
        }
        printf("No room data found. Initialized rooms.\n");
    }
}

void saveData() {
    FILE *patients_file_ptr = fopen(patients_file, "wb");
    if (patients_file_ptr) {
        fwrite(&patient_count, sizeof(int), 1, patients_file_ptr);
        fwrite(patients, sizeof(Patient), patient_count, patients_file_ptr);
        fclose(patients_file_ptr);
        printf("Patient data saved.\n");
    } else {
        printf("Error saving patient data.\n");
    }

    FILE *appointments_file_ptr = fopen(appointments_file, "wb");
    if (appointments_file_ptr) {
        fwrite(&appointment_count, sizeof(int), 1, appointments_file_ptr);
        fwrite(appointments, sizeof(Appointment), appointment_count, appointments_file_ptr);
        fclose(appointments_file_ptr);
        printf("Appointment data saved.\n");
    } else {
        printf("Error saving appointment data.\n");
    }

    FILE *medicines_file_ptr = fopen(medicines_file, "wb");
    if (medicines_file_ptr) {
        fwrite(&medicine_count, sizeof(int), 1, medicines_file_ptr);
        fwrite(medicines, sizeof(Medicine), medicine_count, medicines_file_ptr);
        fclose(medicines_file_ptr);
        printf("Medicine data saved.\n");
    } else {
        printf("Error saving medicine data.\n");
    }

    FILE *rooms_file_ptr = fopen(rooms_file, "wb");
    if (rooms_file_ptr) {
        fwrite(rooms, sizeof(Room), MAX_ROOMS, rooms_file_ptr);
        fclose(rooms_file_ptr);
        printf("Room data saved.\n");
    } else {
        printf("Error saving room data.\n");
    }
}