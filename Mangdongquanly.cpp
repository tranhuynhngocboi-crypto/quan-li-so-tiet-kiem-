#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// Dinh nghia cau truc cho mot So Tiet Kiem
struct SoTietKiem {
    char maSo[20];       // Ma so tiet kiem
    char hoTenKH[50];    // Ho ten khach hang
    double soTienGui;    // So tien gui
    int thoiHan;         // Thoi han gui (thang)
    double laiSuat;      // Lai suat (%/nam)
};

// Khai bao cac ham chuc nang
void nhapDanhSach(SoTietKiem* ds, int batDau, int soLuongMoi);
void xuatDanhSach(SoTietKiem* ds, int n);
void timKiemTheoMa(SoTietKiem* ds, int n, const char* maCanTim);
void sapXepTangDanTheoTien(SoTietKiem* ds, int n);
SoTietKiem* themSoTietKiemMoi(SoTietKiem* dsCu, int& nCu, int soLuongThem);

int main() {
    // Thiet lap dinh dang so thuc cho tien te va phan tram
    cout << fixed << setprecision(2);

    SoTietKiem* ds = NULL; // Con tro quan ly danh sach tong
    int n = 0;             // Tong so luong so hien co
    int luaChon;

    do {
        cout << "\n==================== MENU QUAN LY SO TIET KIEM ====================\n";
        cout << " 1. Nhap them so tiet kiem \n";
        cout << " 2. Xuat danh sach toan bo so tiet kiem \n";
        cout << " 3. Tim kiem so tiet kiem theo ma so\n";
        cout << " 4. Sap xep danh sach so tiet kiem tang dan theo so tien gui\n";
        cout << " 0. Thoat chuong trinh\n";
        cout << "====================================================================\n";
        cout << "Nhap lua chon cua ban (0-4): ";
        cin >> luaChon;

        switch (luaChon) {
        case 1: {
            int soLuongThem;
            cout << "Nhap so luong so tiet kiem muon nhap them: ";
            cin >> soLuongThem;
            if (soLuongThem > 0) {
                // Tu dong cap phat, giu lai danh sach cu va noi tiep du lieu moi vao sau
                ds = themSoTietKiemMoi(ds, n, soLuongThem);
                cout << "Da nhap va ghi nho thanh cong! Tong so so hien tai la: " << n << "\n";
            }
            else {
                cout << "So luong nhap khong hop le!\n";
            }
            break;
        }
        case 2: {
            if (ds == NULL || n <= 0) {
                cout << "Danh sach trong! Vui long nhap du lieu o lua chon 1.\n";
            }
            else {
                xuatDanhSach(ds, n);
            }
            break;
        }
        case 3: {
            if (ds == NULL || n <= 0) {
                cout << "Danh sach trong!\n";
            }
            else {
                char ma[20];
                cout << "Nhap ma so can tim: ";
                cin >> ws;
                cin.getline(ma, 20);
                timKiemTheoMa(ds, n, ma);
            }
            break;
        }
        case 4: {
            if (ds == NULL || n <= 0) {
                cout << "Danh sach trong!\n";
            }
            else {
                sapXepTangDanTheoTien(ds, n);
                cout << "Da sap xep danh sach tang dan theo so tien gui thanh cong!\n";
                xuatDanhSach(ds, n);
            }
            break;
        }
        case 0: {
            cout << "Dang thoat chuong trinh. Tam biet!\n";
            break;
        }
        default: {
            cout << "Lua chon khong hop le! Vui long chon tu 0 den 4.\n";
            break;
        }
        }
    } while (luaChon != 0);

    // Giai phong bo nho truoc khi ket thuc chuong trinh
    if (ds != NULL) {
        delete[] ds;
        ds = NULL;
    }

    return 0;
}

// Ham nhap danh sach tu vi tri 'batDau' với 'soLuongMoi' phan tu
void nhapDanhSach(SoTietKiem* ds, int batDau, int soLuongMoi) {
    cout << "\n--- NHAP THONG TIN SO TIET KIEM ---\n";
    for (int i = 0; i < soLuongMoi; i++) {
        int index = batDau + i;
        cout << "Nhap thong tin cho so thu " << index + 1 << ":\n";
        cout << " - Ma so: ";
        cin >> ws;
        cin.getline((ds + index)->maSo, 20);
        cout << " - Ho ten khach hang: ";
        cin.getline((ds + index)->hoTenKH, 50);
        cout << " - So tien gui (VND): ";
        cin >> (ds + index)->soTienGui;
        cout << " - Thoi han gui (thang): ";
        cin >> (ds + index)->thoiHan;
        cout << " - Lai suat (%/nam): ";
        cin >> (ds + index)->laiSuat;
    }
}

// Ham mo rong mang dong de giu lai so cu va tiep tuc nhap so moi
SoTietKiem* themSoTietKiemMoi(SoTietKiem* dsCu, int& nCu, int soLuongThem) {
    int nMoi = nCu + soLuongThem;
    SoTietKiem* dsMoi = new SoTietKiem[nMoi]; // Cap phat vung nho moi du cho ca cu va moi

    // Sao chep toan bo du lieu cu sang mang moi
    for (int i = 0; i < nCu; i++) {
        *(dsMoi + i) = *(dsCu + i);
    }

    // Giai phong vung nho cu neu da ton tai truoc do
    if (dsCu != NULL) {
        delete[] dsCu;
    }

    // Nhap tiep thong tin cho cac phan tu moi vao phia sau danh sach cu
    nhapDanhSach(dsMoi, nCu, soLuongThem);

    // Cap nhat lai tong so luong
    nCu = nMoi;
    return dsMoi;
}

// Dinh nghia ham xuat danh sach (hien thi chung ca cu va moi)
void xuatDanhSach(SoTietKiem* ds, int n) {
    cout << "\n============================== DANH SACH SO TIET KIEM (Tong: " << n << ") ==============================\n";
    cout << left << setw(10) << "STT"
        << setw(15) << "Ma So"
        << setw(25) << "Ho Ten KH"
        << setw(18) << "So Tien Gui"
        << setw(12) << "Thoi Han"
        << setw(12) << "Lai Suat" << endl;
    cout << "----------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << (i + 1)
            << setw(15) << (ds + i)->maSo
            << setw(25) << (ds + i)->hoTenKH
            << setw(18) << (ds + i)->soTienGui
            << setw(12) << (ds + i)->thoiHan
            << setw(12) << (ds + i)->laiSuat << endl;
    }
    cout << "====================================================================================================\n";
}

// Ham tim kiem tren toan bo danh sach (hien thi tat ca ket qua trung ma tu cu den moi)
void timKiemTheoMa(SoTietKiem* ds, int n, const char* maCanTim) {
    int dem = 0;
    cout << "\n--- KET QUA TIM KIEM CHO MA: " << maCanTim << " ---\n";
    for (int i = 0; i < n; i++) {
        if (strcmp((ds + i)->maSo, maCanTim) == 0) {
            cout << "Tim thay tai vi tri so " << i + 1 << ":\n";
            cout << " - Ho ten KH: " << (ds + i)->hoTenKH << "\n";
            cout << " - So tien gui: " << (ds + i)->soTienGui << " VND\n";
            cout << " - Thoi han: " << (ds + i)->thoiHan << " thang\n";
            cout << " - Lai suat: " << (ds + i)->laiSuat << "%/nam\n";
            cout << "----------------------------------------\n";
            dem++;
        }
    }
    if (dem == 0) {
        cout << "Khong tim thay so tiet kiem nao co ma \"" << maCanTim << "\" trong he thong!\n";
    }
    else {
        cout << "Da tim thay tong cong " << dem << " so co chung ma nay (bao gom ca danh sach cu va moi).\n";
    }
}

// Ham sap xep tang dan theo so tien gui tren toan bo danh sach
void sapXepTangDanTheoTien(SoTietKiem* ds, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((ds + i)->soTienGui > (ds + j)->soTienGui) {
                SoTietKiem temp = *(ds + i);
                *(ds + i) = *(ds + j);
                *(ds + j) = temp;
            }
        }
    }
}