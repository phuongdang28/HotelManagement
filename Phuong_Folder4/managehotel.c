#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ADMIN_PASSWORD "123456" // Mật khẩu mặc định cho quản lý

// Cấu trúc phòng
typedef struct Room {
    int roomNumber;
    char roomType[20];
    int price;
    int isAvailable; // 1: Phòng trống, 0: Phòng đã đặt
} Room;

// Cấu trúc khách sạn
typedef struct Hotel {
    int hotelID;
    char hotelName[50];
    Room room;
    struct Hotel* next;
} Hotel;

// Cấu trúc khách hàng
typedef struct Customer {
    int customerID;
    char name[50];
    char phone[15];
    char password[20];  // Thêm mật khẩu cho tài khoản
    struct Customer* next;
} Customer;

// Danh sách khách sạn và khách hàng
Hotel* hotelList = NULL;
Customer* customerList = NULL;
// Biến toàn cục lưu thông tin khách hàng đang đăng nhập
Customer* currentCustomer = NULL;

// Chức năng thêm khách sạn mới
void addHotel(int hotelID, const char* hotelName, int roomNumber, const char* roomType, int price) {
    Hotel* newHotel = (Hotel*)malloc(sizeof(Hotel));
    newHotel->hotelID = hotelID;
    strcpy(newHotel->hotelName, hotelName);
    newHotel->room.roomNumber = roomNumber;
    strcpy(newHotel->room.roomType, roomType);
    newHotel->room.price = price;
    newHotel->room.isAvailable = 1; // Mặc định phòng trống
    newHotel->next = hotelList;
    hotelList = newHotel;
    printf("Thêm khách sạn thành công!\n");
}

// Hàm kiểm tra tên hợp lệ
int isValidName(const char* name) {
    int length = strlen(name);
    // Kiểm tra độ dài
    if (length < 2 || length > 50) {
        return 0; // Không hợp lệ
    }
    // Kiểm tra các ký tự trong tên (chỉ chứa chữ cái và khoảng trắng)
    for (int i = 0; i < length; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0; // Không hợp lệ
        }
    }
    return 1; // Hợp lệ
}

// Hàm kiểm tra số điện thoại hợp lệ
int isValidPhoneNumber(const char* phone) {
    // Kiểm tra chiều dài (10 chữ số)
    int length = strlen(phone);
    if (length != 10) {
        return 0; // Không hợp lệ
    }

    // Kiểm tra ký tự đầu tiên là '0'
    if (phone[0] != '0') {
        return 0; // Không hợp lệ
    }

    // Kiểm tra tất cả các ký tự là số
    for (int i = 0; i < length; i++) {
        if (!isdigit(phone[i])) {
            return 0; // Không hợp lệ
        }
    }
    return 1; // Hợp lệ
}

// Hàm gán ID tự động cho khách hàng
int generateCustomerID() {
    if (customerList == NULL) {
        return 1;  // Nếu danh sách trống, gán ID là 1
    }
    Customer* current = customerList;
    int maxID = 0;  // Khởi tạo ID lớn nhất là 0
    while (current != NULL) {
        if (current->customerID > maxID) {
            maxID = current->customerID;  // Cập nhật ID lớn nhất
        }
        current = current->next;
    }
    return maxID + 1;  // Gán ID tiếp theo là ID lớn nhất + 1
}

// Chức năng thêm khách hàng mới
void addCustomer(int customerID, const char* name, const char* phone, const char* password) {
    // Kiểm tra tên và số điện thoại hợp lệ
    while (!isValidName(name) || !isValidPhoneNumber(phone)) {
        if (!isValidName(name)) {
            printf("Tên không hợp lệ! Tên chỉ được chứa chữ cái và khoảng trắng (2-50 ký tự).\n");
            printf("Nhập tên khách hàng: ");
            scanf(" %[^\n]", name);
        }
        if (!isValidPhoneNumber(phone)) {
            printf("Số điện thoại không hợp lệ! Vui lòng nhập lại.\n");
            printf("Nhập số điện thoại: ");
            scanf("%s", phone);
        }
    }
    // Gán ID mới cho khách hàng nếu không được truyền ID
    if (customerID == 0) {
        customerID = generateCustomerID();
    }
    // Thêm khách hàng vào danh sách
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    newCustomer->customerID = customerID;
    strcpy(newCustomer->name, name);
    strcpy(newCustomer->phone, phone);
    strcpy(newCustomer->password, password);  // Lưu mật khẩu cho khách hàng
    newCustomer->next = customerList;
    customerList = newCustomer;
    printf("Thêm khách hàng thành công!\n");
}

// Hàm khởi tạo dữ liệu ban đầu
void initializeData() {
    // Thêm 10 khách sạn
    addHotel(1, "Hotel A", 101, "Standard", 500000);
    addHotel(2, "Hotel B", 102, "Deluxe", 800000);
    addHotel(3, "Hotel C", 103, "Suite", 1500000);
    addHotel(4, "Hotel D", 104, "Standard", 450000);
    addHotel(5, "Hotel E", 105, "Deluxe", 900000);
    addHotel(6, "Hotel F", 106, "Suite", 2000000);
    addHotel(7, "Hotel G", 107, "Standard", 400000);
    addHotel(8, "Hotel H", 108, "Deluxe", 1000000);
    addHotel(9, "Hotel I", 109, "Suite", 1800000);
    addHotel(10, "Hotel J", 110, "Standard", 550000);

    // Thêm 15 khách hàng
    addCustomer(1, "Nguyen Van A", "0123456789", "password123");
    addCustomer(2, "Tran Thi B", "0987654321", "mypassword456");
    addCustomer(3, "Le Van C", "0912345678", "123password789");
    addCustomer(4, "Pham Thi D", "0934567890", "securepass001");
    addCustomer(5, "Hoang Van E", "0945678901", "qwerty098");
    addCustomer(6, "Ngo Thi F", "0967890123", "iloveyou123");
    addCustomer(7, "Dang Van G", "0978901234", "abcde12345");
    addCustomer(8, "Bui Thi H", "0990123456", "letmein678");
    addCustomer(9, "Do Van I", "0901234567", "12345abcde");
    addCustomer(10, "Ly Thi J", "0923456789", "password987");
    addCustomer(11, "Vo Van K", "0913456789", "strongpassword1");
    addCustomer(12, "Cao Thi L", "0935678901", "complexpass234");
    addCustomer(13, "Phan Van M", "0947890123", "password2024");
    addCustomer(14, "Trinh Thi N", "0968901234", "securekey567");
    addCustomer(15, "Ta Van O", "0979012345", "mypassword999");
}

// Hàm tìm khách hàng theo ID 
Customer* findCustomerByID(int customerID) {
    Customer* current = customerList;
    while (current != NULL) {
        if (current->customerID == customerID) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Hàm đăng ký tài khoản khách hàng mới
void registerCustomer(const char* name, const char* phone, const char* password) {
    int customerID = generateCustomerID(); // Tạo ID cho khách hàng mới
    addCustomer(customerID, name, phone, password); // Thêm khách hàng vào danh sách
    // Lưu thông tin khách hàng vào biến toàn cục
    currentCustomer = findCustomerByID(customerID);
    printf("Đăng ký thành công! Mã khách hàng của bạn là: %d\n", customerID);
}

// Hàm kiểm tra thông tin tài khoản (đăng nhập)
int loginCustomer(char* name, char* phone, char* password) {
    Customer* current = customerList;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->phone, phone) == 0) {
            if (strcmp(current->password, password) == 0) {
                currentCustomer = current;  // Lưu thông tin khách hàng vào biến toàn cục
                return 1; // Đăng nhập thành công
            } else {
                printf("Mật khẩu không chính xác!\n");
                return 0;
            }
        }
        current = current->next;
    }

    // Nếu không tìm thấy khách hàng, hỏi người dùng có muốn đăng ký không
    printf("Thông tin đăng nhập không hợp lệ. Bạn có muốn đăng ký tài khoản mới không? (y/n): ");
    char choice;
    scanf(" %c", &choice);  // Đọc lựa chọn từ người dùng
    if (choice == 'y' || choice == 'Y') {
        // Yêu cầu người dùng nhập mật khẩu và gọi hàm đăng ký
        char newPassword[50]; 
        printf("Nhập mật khẩu (không chứa ký tự ' '): ");
        scanf("%s", newPassword);
        registerCustomer(name, phone, newPassword);  // Gọi hàm đăng ký
        return 1; // Đăng ký thành công, có thể đăng nhập ngay sau đó
    }

    return 0; // Không đăng ký, quay lại
}

// Hàm kiểm tra tài khoản (Đăng nhập/Đăng ký)
void checkAccount() {
    char name[50];
    char phone[15];
    char password[20];
    int choice;

    printf("Bạn đã có tài khoản chưa?\n");
    printf("1. Đăng nhập\n");
    printf("2. Đăng ký\n");
    printf("Lựa chọn của bạn: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Đăng nhập
            printf("Nhập tên khách hàng: ");
            scanf(" %[^\n]", name);
            printf("Nhập số điện thoại: ");
            scanf("%s", phone);
            printf("Nhập mật khẩu: ");
            scanf("%s", password);

            // Kiểm tra thông tin đăng nhập
            if (!loginCustomer(name, phone, password)) {
                printf("Đăng nhập thất bại. Bạn có muốn thử lại không? (1: Có, 0: Không): ");
                scanf("%d", &choice);
                if (choice == 1) {
                    checkAccount();  // Gọi lại hàm kiểm tra tài khoản để thử lại
                } else {
                    printf("Quay lại menu chính.\n");
                }
            } else {
                printf("Đăng nhập thành công!\n");
            }
            break;
        case 2: // Đăng ký
            printf("Nhập tên khách hàng: ");
            char name[50];
            scanf(" %[^\n]", name);  // Đọc tên có khoảng trắng

            // Kiểm tra tính hợp lệ của tên
            if (!isValidName(name)) {
                printf("Tên không hợp lệ. Vui lòng nhập lại.\n");
                return;
            }
            printf("Nhập số điện thoại: ");
            scanf("%s", phone);
            // Kiểm tra tính hợp lệ của số điện thoại
            if (!isValidPhoneNumber(phone)) {
                printf("Số điện thoại không hợp lệ. Vui lòng nhập lại.\n");
                return;
            }
            // Yêu cầu mật khẩu có ít nhất 8 ký tự
            do {
                printf("Nhập mật khẩu (ít nhất 8 ký tự): ");
                scanf("%s", password);
                if (strlen(password) < 8) {
                    printf("Mật khẩu phải có ít nhất 8 ký tự. Vui lòng nhập lại.\n");
                }
            } while (strlen(password) < 8);
            // Tạo ID khách hàng mới và đăng ký
            int customerID = (customerList == NULL) ? 1 : customerList->customerID + 1;  // Gán ID mới
            registerCustomer(name, phone, password);
            break;
        default:
            printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
            break;
    }
}

// Kiểm tra phòng trống trong tất cả các khách sạn
void checkAvailableRooms() {
    Hotel* current = hotelList;
    printf("Danh sách các phòng trống:\n");
    while (current != NULL) {
        if (current->room.isAvailable) {
            printf("Khách sạn %s (ID: %d) - Phòng %d - Loại: %s - Giá: %d\n",
                   current->hotelName, current->hotelID, current->room.roomNumber, 
                   current->room.roomType, current->room.price);
        }
        current = current->next;
    }
}

// Đặt phòng trong khách sạn
void bookRoom(int hotelID) {
    // Tìm khách sạn
    Hotel* currentHotel = hotelList;
    while (currentHotel != NULL && currentHotel->hotelID != hotelID) {
        currentHotel = currentHotel->next;
    }
    if (currentHotel == NULL) {
        printf("Khách sạn không tồn tại.\n");
        return;
    }
    if (!currentHotel->room.isAvailable) {
        printf("Phòng đã được đặt.\n");
        return;
    }
    // Đặt phòng cho khách hàng đã đăng ký hoặc đăng nhập
    currentHotel->room.isAvailable = 0;
    printf("Đặt phòng thành công tại khách sạn %s (ID: %d) cho khách hàng %s (ID: %d)!\n",
           currentHotel->hotelName, hotelID, currentCustomer->name, currentCustomer->customerID);
}

// Hiển thị danh sách khách sạn
void displayHotels() {
    if (hotelList == NULL) {
        printf("Danh sách khách sạn rỗng.\n");
        return;
    }
    Hotel* current = hotelList;
    printf("Danh sách khách sạn:\n");
    while (current != NULL) {
        printf("Khách sạn %s (ID: %d) - Phòng %d - Loại: %s - Giá: %d - Tình trạng: %s\n",
               current->hotelName, current->hotelID, current->room.roomNumber,
               current->room.roomType, current->room.price,
               current->room.isAvailable ? "Trống" : "Đã đặt");
        current = current->next;
    }
}

// Hiển thị danh sách khách hàng
void displayCustomers() {
    if (customerList == NULL) {
        printf("Danh sách khách hàng rỗng.\n");
        return;
    }
    Customer* current = customerList;
    printf("Danh sách khách hàng:\n");
    while (current != NULL) {
        printf("ID: %d - Tên: %s - Số điện thoại: %s\n", current->customerID, current->name, current->phone);
        current = current->next;
    }
}

// Xóa khách sạn khỏi danh sách
void deleteHotel(int hotelID) {
    Hotel* current = hotelList;
    Hotel* prev = NULL;

    while (current != NULL && current->hotelID != hotelID) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Khách sạn không tồn tại.\n");
        return;
    }
    if (prev == NULL) {
        hotelList = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("Đã xóa khách sạn thành công.\n");
}

// Xóa khách hàng khỏi danh sách
void deleteCustomer(int customerID) {
    Customer* current = customerList;
    Customer* prev = NULL;

    while (current != NULL && current->customerID != customerID) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Khách hàng không tồn tại.\n");
        return;
    }
    if (prev == NULL) {
        customerList = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("Đã xóa khách hàng thành công.\n");
}

// Kiểm tra mật khẩu quản lý
int verifyPassword() {
    char inputPassword[20];
    printf("Nhập mật khẩu quản lý: ");
    scanf("%s", inputPassword);

    if (strcmp(inputPassword, ADMIN_PASSWORD) == 0) {
        printf("Đăng nhập thành công!\n");
        return 1; // Mật khẩu đúng
    } else {
        printf("Mật khẩu sai. Quay lại menu chính.\n");
        return 0; // Mật khẩu sai
    }
}

// Nhập chuỗi an toàn
void inputString(char* prompt, char* str, int size) {
    printf("%s", prompt);
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0'; // Xóa ký tự xuống dòng nếu có
}

// Menu của Quản lý
void managerMenu() {
    int choice, hotelID, roomNumber, price, customerID;
    char hotelName[50], roomType[20], name[50], phone[15], password[20];

    while (1) {
        printf("\n--- Quản lý khách sạn ---\n");
        printf("1. Thêm khách sạn\n");
        printf("2. Thêm khách hàng\n");
        printf("3. Kiểm tra phòng trống\n");
        printf("4. Đặt phòng\n");
        printf("5. Hiển thị tất cả khách sạn\n");
        printf("6. Hiển thị tất cả khách hàng\n");
        printf("7. Xóa khách sạn\n");
        printf("8. Xóa khách hàng\n");
        printf("0. Quay lại\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhập ID khách sạn: ");
                scanf("%d", &hotelID);
                // Kiểm tra ID hợp lệ
                if (hotelID <= 0) {
                    printf("ID khách sạn không hợp lệ.\n");
                    return;
                }
                getchar(); // Dọn dẹp bộ đệm
                printf("Nhập tên khách sạn: ");
                fgets(hotelName, sizeof(hotelName), stdin);
                hotelName[strcspn(hotelName, "\n")] = '\0'; // Loại bỏ ký tự newline
                printf("Nhập số phòng: ");
                scanf("%d", &roomNumber);
                printf("Nhập loại phòng: ");
                getchar(); // Dọn dẹp bộ đệm
                fgets(roomType, sizeof(roomType), stdin);
                roomType[strcspn(roomType, "\n")] = '\0';
                printf("Nhập giá phòng: ");
                scanf("%d", &price);
                addHotel(hotelID, hotelName, roomNumber, roomType, price);
                break;
            case 2:
                printf("Nhập ID khách hàng: ");
                scanf("%d", &customerID);
                if (customerID <= 0) {
                    printf("ID khách hàng không hợp lệ.\n");
                    return;
                }
                getchar(); // Dọn dẹp bộ đệm
                printf("Nhập tên khách hàng: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Loại bỏ ký tự newline
                printf("Nhập số điện thoại: ");
                scanf("%s", phone);
                printf("Nhập mật khẩu: ");
                scanf("%s", password);
                addCustomer(customerID, name, phone, password);
                break;
            case 3:
                checkAvailableRooms();
                break;
            case 4:
                printf("Nhập ID khách sạn: ");
                scanf("%d", &hotelID);
                getchar();
                printf("Nhập tên khách hàng: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Nhập số điện thoại khách hàng: ");
                scanf("%s", phone);
                bookRoom(hotelID);
                break;
            case 5:
                displayHotels();
                break;
            case 6:
                displayCustomers();
                break;
            case 7:
                printf("Nhập ID khách sạn cần xóa: ");
                scanf("%d", &hotelID);
                deleteHotel(hotelID);
                break;
            case 8:
                printf("Nhập ID khách hàng cần xóa: ");
                scanf("%d", &customerID);
                deleteCustomer(customerID);
                break;
            case 0:
                return; // Quay lại menu chính
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }
    }
}

// Menu của Khách hàng
void customerMenu() {
    int choice, hotelID;
    char name[50], phone[15];

    while (1) {
        printf("\n--- Dành cho khách hàng ---\n");
        printf("1. Kiểm tra phòng trống\n");
        printf("2. Đặt phòng\n");
        printf("3. Xem danh sách khách sạn\n");
        printf("0. Quay lại\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkAvailableRooms();
                break;
            case 2:
                printf("Nhập ID khách sạn: ");
                scanf("%d", &hotelID);
                getchar(); // Xóa ký tự thừa sau scanf
                bookRoom(hotelID);
                break;
            case 3:
                displayHotels();
                break;
            case 0:
                return; // Quay lại menu chính
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }
    }
}

// Menu chính chọn vai trò
void mainMenu() {
    int roleChoice;
    while (1) {
        printf("\n--- Hệ thống quản lý khách sạn ---\n");
        printf("1. Quản lý\n");
        printf("2. Khách hàng\n");
        printf("0. Thoát\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &roleChoice);

        switch (roleChoice) {
            case 1:
                if (verifyPassword()) {
                    managerMenu(); // Menu của quản lý
                }
                break;
            case 2:
                // Trước khi vào menu khách hàng, yêu cầu đăng nhập hoặc đăng ký
                checkAccount(); // Đăng nhập/Đăng ký
                customerMenu(); // Menu của khách hàng
                break;
            case 0:
                printf("Thoát chương trình.\n");
                return;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }
    }
}

int main() {
    initializeData(); // Khởi tạo dữ liệu ban đầu
    mainMenu();       // Chọn vai trò và hiển thị menu tương ứng
    return 0;
}
