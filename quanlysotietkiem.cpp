#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

// Cấu trúc đại diện cho một Sổ tiết kiệm
struct SoTietKiem {
    std::string maSo;
    std::string tenKhachHang;
    double soTienGui;
    double laiSuat;
    int kyHan; // tính theo tháng
};

// --- THUẬT TOÁN 1: SELECTION SORT ---
// Sắp xếp danh sách sổ tiết kiệm tăng dần theo Số tiền gửi
void selectionSort(std::vector<SoTietKiem>& danhSach) {
    int n = danhSach.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (danhSach[j].soTienGui < danhSach[minIdx].soTienGui) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(danhSach[i], danhSach[minIdx]);
        }
    }
}

// --- THUẬT TOÁN 2: TÌM KIẾM NHỊ PHÂN ĐỆ QUY ---
// Hàm đệ quy phụ trợ (Helper function)
int binarySearchRecursiveHelper(const std::vector<SoTietKiem>& danhSach, int left, int right, double target) {
    if (left > right) {
        return -1; // Không tìm thấy
    }

    int mid = left + (right - left) / 2; // Tránh tràn số nguyên

    if (danhSach[mid].soTienGui == target) {
        return mid; // Tìm thấy tại vị trí mid
    }
    
    // Nếu giá trị cần tìm nhỏ hơn phần tử ở giữa, tìm ở nửa bên trái
    if (danhSach[mid].soTienGui > target) {
        return binarySearchRecursiveHelper(danhSach, left, mid - 1, target);
    }
    
    // Ngược lại, tìm ở nửa bên phải
    return binarySearchRecursiveHelper(danhSach, mid + 1, right, target);
}

// Hàm tìm kiếm nhị phân đệ quy chính giao tiếp với người dùng
int binarySearchRecursive(const std::vector<SoTietKiem>& danhSach, double target) {
    return binarySearchRecursiveHelper(danhSach, 0, danhSach.size() - 1, target);
}

// Hàm hiển thị danh sách dưới dạng bảng
void hienThiDanhSach(const std::vector<SoTietKiem>& danhSach) {
    if (danhSach.empty()) {
        std::cout << "\n[Thong bao] Danh sach so tiet kiem hien dang trong!\n";
        return;
    }
    std::cout << "\n" << std::string(75, '=') << "\n";
    std::cout << std::left << std::setw(10) << "MA SO" 
              << std::setw(22) << "KHACH HANG" 
              << std::setw(18) << "SO TIEN (VND)" 
              << std::setw(12) << "LAI SUAT(%)" 
              << std::setw(13) << "KY HAN (THANG)" << "\n";
    std::cout << std::string(75, '-') << "\n";
    for (const auto& s : danhSach) {
        std::cout << std::left << std::setw(10) << s.maSo 
                  << std::setw(22) << s.tenKhachHang 
                  << std::setw(18) << std::fixed << std::setprecision(0) << s.soTienGui 
                  << std::setw(12) << std::fixed << std::setprecision(2) << s.laiSuat 
                  << std::setw(13) << s.kyHan << "\n";
    }
    std::cout << std::string(75, '=') << "\n";
}

// Hàm hiển thị màn hình menu chính
void hienThiMenu() {
    std::cout << "\n================ CHUONG TRINH QUAN LY SO TIET KIEM ================\n";
    std::cout << "1. Them so tiet kiem moi\n";
    std::cout << "2. Hien thi danh sach so tiet kiem\n";
    std::cout << "3. Sap xep danh sach tang dan theo so tien (Selection Sort)\n";
    std::cout << "4. Tim kiem so tiet kiem theo so tien (Tim kiem nhi phan de quy)\n";
    std::cout << "5. Thoat chuong trinh\n";
    std::cout << "===================================================================\n";
    std::cout << "Nhap lua chon cua ban (1-5): ";
}

int main() {
    std::vector<SoTietKiem> nganHang;
    int luaChon;

    do {
        hienThiMenu();
        if (!(std::cin >> luaChon)) {
            std::cout << "Loi: Vui long nhap mot so nguyen hop le!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Xóa bộ đệm

        switch (luaChon) {
            case 1: {
                SoTietKiem s;
                std::cout << "\n--- NHAP THONG TIN SO TIET KIEM ---\n";
                std::cout << "Nhap ma so (VD: S001): ";
                std::getline(std::cin, s.maSo);
                std::cout << "Nhap ten khach hang: ";
                std::getline(std::cin, s.tenKhachHang);
                std::cout << "Nhap so tien gui (VND): ";
                std::cin >> s.soTienGui;
                std::cout << "Nhap lai suat (%/nam): ";
                std::cin >> s.laiSuat;
                std::cout << "Nhap ky han (thang): ";
                std::cin >> s.kyHan;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                nganHang.push_back(s);
                std::cout << "-> [Thanh cong] Da them so tiet kiem vao he thong!\n";
                break;
            }
            case 2:
                hienThiDanhSach(nganHang);
                break;
            case 3:
                if (nganHang.empty()) {
                    std::cout << "\n[Canh bao] Danh sach trong, khong the sap xep!\n";
                } else {
                    selectionSort(nganHang);
                    std::cout << "\n-> [Thanh cong] Da sap xep danh sach tang dan theo so tien!\n";
                    hienThiDanhSach(nganHang);
                }
                break;
            case 4: {
                if (nganHang.empty()) {
                    std::cout << "\n[Canh bao] Danh sach trong, khong the tim kiem!\n";
                    break;
                }
                double target;
                std::cout << "\nNhap so tien can tim kiem: ";
                std::cin >> target;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Thuật toán tìm kiếm nhị phân yêu cầu mảng phải được sắp xếp trước
                std::cout << "(Luu y: He thong tu dong sap xep danh sach de dam bảo ket qua tim kiem chinh xac...)\n";
                selectionSort(nganHang);

                int ketQua = binarySearchRecursive(nganHang, target);
                if (ketQua != -1) {
                    std::cout << "\n-> [Tim thay] Thay so tiet kiem tai vi tri index " << ketQua << ":\n";
                    std::cout << "   - Ma so: " << nganHang[ketQua].maSo << "\n";
                    std::cout << "   - Khach hang: " << nganHang[ketQua].tenKhachHang << "\n";
                    std::cout << "   - So tien: " << std::fixed << std::setprecision(0) << nganHang[ketQua].soTienGui << " VND\n";
                    std::cout << "   - Lai suat: " << nganHang[ketQua].laiSuat << "%/nam\n";
                    std::cout << "   - Ky han: " << nganHang[ketQua].kyHan << " thang\n";
                } else {
                    std::cout << "\n-> [Khong tim thay] Khong ton tai so tiet kiem co so tien la " << target << " VND.\n";
                }
                break;
            }
            case 5:
                std::cout << "\nTam biet! Cam on ban da su dung chuong trinh.\n";
                break;
            default:
                std::cout << "\n[Loi] Lua chon khong hop le! Vui long chon tu 1 den 5.\n";
        }
    } while (luaChon != 5);

    return 0;
}