#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SinhVien {
protected:
    string maSV, hoTen;

public:
    virtual void nhap() {
        cin.ignore();
        cout << "Nhap ma SV: ";
        getline(cin, maSV);
        cout << "Nhap ho ten: ";
        getline(cin, hoTen);
    }

    virtual float tinhDiemTB() = 0;

    virtual void hienThi() {
        cout << "Ma SV: " << maSV << endl;
        cout << "Ho ten: " << hoTen << endl;
        cout << "Diem TB: " << tinhDiemTB() << endl;
    }

    string getTen() {
        return hoTen;
    }

    virtual ~SinhVien() {}
};

class SinhVienCNTT : public SinhVien {
private:
    float diemLapTrinh, diemCSDL;

public:
    void nhap() override {
        SinhVien::nhap();
        cout << "Nhap diem lap trinh: ";
        cin >> diemLapTrinh;
        cout << "Nhap diem CSDL: ";
        cin >> diemCSDL;
    }

    float tinhDiemTB() override {
        return (diemLapTrinh + diemCSDL) / 2;
    }
};

class SinhVienKinhTe : public SinhVien {
private:
    float diemKT, diemMarketing;

public:
    void nhap() override {
        SinhVien::nhap();
        cout << "Nhap diem kinh te: ";
        cin >> diemKT;
        cout << "Nhap diem marketing: ";
        cin >> diemMarketing;
    }

    float tinhDiemTB() override {
        return (diemKT + diemMarketing) / 2;
    }
};

// ====== HÀM XỬ LÝ ======

void themSinhVien(vector<SinhVien*>& ds) {
    int loai;
    cout << "Chon loai (1-CNTT, 2-Kinh Te): ";
    cin >> loai;

    SinhVien* sv;

    if (loai == 1)
        sv = new SinhVienCNTT();
    else
        sv = new SinhVienKinhTe();

    sv->nhap();
    ds.push_back(sv);
}

void hienThiDS(vector<SinhVien*> ds) {
    for (auto sv : ds) {
        cout << "-----------------\n";
        sv->hienThi();
    }
}

void timTheoTen(vector<SinhVien*> ds) {
    string ten;
    cin.ignore();
    cout << "Nhap ten can tim: ";
    getline(cin, ten);

    for (auto sv : ds) {
        if (sv->getTen().find(ten) != string::npos) {
            sv->hienThi();
        }
    }
}

void sapXep(vector<SinhVien*>& ds) {
    for (int i = 0; i < ds.size(); i++) {
        for (int j = i + 1; j < ds.size(); j++) {
            if (ds[i]->tinhDiemTB() < ds[j]->tinhDiemTB()) {
                swap(ds[i], ds[j]);
            }
        }
    }
}

void timMax(vector<SinhVien*> ds) {
    float max = -1;
    SinhVien* svMax = nullptr;

    for (auto sv : ds) {
        if (sv->tinhDiemTB() > max) {
            max = sv->tinhDiemTB();
            svMax = sv;
        }
    }

    cout << "\nSinh vien diem cao nhat:\n";
    if (svMax)
        svMax->hienThi();
}

// ====== MAIN ======

int main() {
    vector<SinhVien*> ds;
    int chon;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Tim theo ten\n";
        cout << "4. Sap xep theo diem\n";
        cout << "5. Tim diem cao nhat\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
        case 1:
            themSinhVien(ds);
            break;
        case 2:
            hienThiDS(ds);
            break;
        case 3:
            timTheoTen(ds);
            break;
        case 4:
            sapXep(ds);
            cout << "Da sap xep!\n";
            break;
        case 5:
            timMax(ds);
            break;
        }

    } while (chon != 0);

    return 0;
}
