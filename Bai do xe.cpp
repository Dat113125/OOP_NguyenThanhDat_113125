#include<iostream>
#include<string>
#include<cctype>
using namespace std;

class Vihecle{
	private:
		int vihecleID;
		string vihecleType;
		int entryTime;
		int parkingDuration;
		double parkingFee;
		bool isOccupied;
		
		string chuanhoaten(string type){
			string lower = type;
			if(lower == "car") return "Car";
			if(lower == "motorcycle") return "Motorcycle";
			if(lower == "bicycle") return "Bicycle";
			return type;
		}
		
	public:
		Vihecle(){
			vihecleID = 0;
			vihecleType = "";
			entryTime = 0;
			parkingDuration = 0;
			parkingFee = 0.0;
			isOccupied = false;
		}
		Vihecle(int vihecleID, string vihecleType, int entryTime, int parkingDuration){
			this->vihecleID = vihecleID;
			this->vihecleType = vihecleType;
			this->entryTime = entryTime;
			this->parkingDuration = parkingDuration;
			isOccupied = true;
			tinhphi();
			
		}
		//Getter
		int getVihecleID(){return vihecleID;}
		string getvihecleType(){return vihecleType;}
		int getentryTime(){return entryTime;}
		int getparkingDuration(){return parkingDuration;}
		double getparkingFee(){return parkingFee;}
		bool getisOccupied(){return isOccupied;}
		
		//Setter
		void setvihecleID(int id){ vihecleID = id;}
		void setvihecleType(string type) { vihecleType = chuanhoaten(type);}
		void setentryTime(int time){ entryTime = time;}
		void setparkingDuration(int duration){parkingDuration = duration;}
		void setisOccoupied(bool occupied){isOccupied = occupied;}
		
		void tinhphi(){
		float phi2hdau, phisau;
		if (vihecleType == "Car"){
			if(parkingDuration <= 2 ){
				if(entryTime == 6 || entryTime == 7 || entryTime == 8 || entryTime == 9 || entryTime == 15 || entryTime == 16 || entryTime == 17 || entryTime == 18){
					phi2hdau = parkingDuration*(6+6*0.3);
				}
				else{
					phi2hdau = parkingDuration*(6-6*0.05);
				}
			}
			else{
				phisau = parkingDuration*(6-6*0.1);
			}
		}
		
		if (vihecleType == "Motorcycle"){
			if(parkingDuration <= 2 ){
				if(entryTime == 6 || entryTime == 7 || entryTime == 8 || entryTime == 9 || entryTime == 15 || entryTime == 16 || entryTime == 17 || entryTime == 18){
					phi2hdau = parkingDuration*(4+4*0.3);
				}
				else{
					phi2hdau = parkingDuration*(4-4*0.05);
				}
			}
			else{
				phisau = parkingDuration*(4-4*0.1);
			}
		}
		
		if (vihecleType == "Bicycle"){
			if(parkingDuration <= 2 ){
				if(entryTime == 6 || entryTime == 7 || entryTime == 8 || entryTime == 9 || entryTime == 15 || entryTime == 16 || entryTime == 17 || entryTime == 18){
					phi2hdau = parkingDuration*(2+2*0.3);
				}
				else{
					phi2hdau = parkingDuration*(2-2*0.05);
				}
			}
			else{
				phisau = parkingDuration*(2-2*0.1);
			}
		}
		float phidoxe = phi2hdau + phisau;
		cout<<"Phi do xe: "<<phidoxe;
	}
	void hienthiVihecle(){
		cout<<"Ma phuong tien"<<vihecleID<<endl;
		cout<<"Loai phuong tien"<<vihecleType<<endl;
		cout<<"Thoi gian vao"<<entryTime<<":00"<<endl;
		cout<<"Thoi gian do xe"<<parkingDuration<<"gio"<<endl;
		cout<<"Phi do xe:";
		tinhphi();
	}
};

class parkingLot{
	private:
		int parkID;
		char size;
		Vihecle Vihecle1, Vihecle2, Vihecle3;
		bool hasVihecle1,  hasVihecle2, hasVihecle3;
		bool isExist;
	public:
		parkingLot(){
			parkID = -1;
			size = 'S';
			hasVihecle1 = false;
			hasVihecle2 = false;
			hasVihecle3 = false;
			isExist = false;
		}
		parkingLot(int parkID, char size){
			this->parkID = parkID;
			this->size = toupper(size);
			hasVihecle1 = true;
			hasVihecle2 = true;
			hasVihecle3 = true;
			isExist = true;
		}
		
		//Getter
		int getparkID() const{return parkID;}
		char getsize() const{return size;}
		bool getisExist() const{return isExist;}
		
		//Setter
		void setparkID(int id) { parkID = id;}
		void setsize(char s){ size = s;}
		void setisExist(bool exist){ isExist = exist;}
		
		bool addVihecle(const Vihecle& v){
			if(!isExist) return false;
			
			if(!hasVihecle1){
				Vihecle1 = v;
				hasVihecle1 = true;
				return true;
			}
			
			if(size == 'M' || size == 'L'){
				if(!hasVihecle2){
					Vihecle2 = v;
					hasVihecle2 = true;
					return true;
				}
			}
			
			if(size == 'L'){
				if(!hasVihecle3){
					Vihecle3 = v;
					hasVihecle3 = true;
					return true;
				}
			}
			return false;
		}
		
		bool removeVihecle(int vID){
			if(hasVihecle1 && Vihecle1.getVihecleID() == vID){
				hasVihecle1 = false;
				Vihecle1 = Vihecle();
				return true;
			}
			
			if(hasVihecle2 && Vihecle2.getVihecleID() == vID){
				hasVihecle2 = false;
				Vihecle2 = Vihecle();
				return true;
			}
			
			if(hasVihecle3 && Vihecle3.getVihecleID() == vID){
				hasVihecle3 = true;
				Vihecle3 = Vihecle();
				return true;
			}
			return false;
		}
		
		bool coVihecleko(int vID){
			return(hasVihecle1 && Vihecle1.getVihecleID() == vID || hasVihecle2 && Vihecle2.getVihecleID() == vID || hasVihecle3 && Vihecle3.getVihecleID() == vID);
		}
	
		Vihecle layViheclequaID(int vID){
			if(hasVihecle1 && Vihecle1.getVihecleID() == vID) return Vihecle1;
			if(hasVihecle2 && Vihecle2.getVihecleID() == vID) return Vihecle2;
			if(hasVihecle3 && Vihecle3.getVihecleID() == vID) return Vihecle3;
			return Vihecle();
		}
		
		int demVihecle(){
			int count = 0;
			if(hasVihecle1) count++;
			if(hasVihecle2) count++;
			if(hasVihecle3) count++;
			return count;
		}
		
		void hienthiLot(){
			cout<<"ID bai do:"<<parkID<<endl;
			cout<<"So xe hien tai:"<<demVihecle()<<endl;
			cout<<"Size:"<<size<<endl;
		}
		
		void hienthithongtinLot(){
			hienthiLot();
			if(demVihecle() == 0){
				cout<<"Bai xe chua co xe nao"<<endl;
			}
			else{
				if(hasVihecle1) Vihecle1.hienthiVihecle();
				if(hasVihecle2) Vihecle2.hienthiVihecle();
				if(hasVihecle3) Vihecle3.hienthiVihecle();
			}
		}
		
		void baocao(string type, double tongphi, int dem){
			if(hasVihecle1 && Vihecle1.getvihecleType() == type){
				tongphi += Vihecle1.getparkingFee();
				dem++;
			}
			else if(hasVihecle2 && Vihecle2.getvihecleType() == type){
				tongphi += Vihecle2.getparkingFee();
				dem++;
			}
			else if(hasVihecle3 && Vihecle3.getvihecleType() == type){
				tongphi += Vihecle3.getparkingFee();
				dem++;
			}
		}
		
		void timtheoType(string type, bool found){
			if(hasVihecle1 && Vihecle1.getvihecleType() == type){
				cout<<"Tim thay tai bai co ID: "<<parkID<<endl;
				Vihecle1.hienthiVihecle();
				found = true;
			}
			
			else if(hasVihecle2 && Vihecle2.getvihecleType() == type){
				cout<<"Tim thay tai bai co ID: "<<parkID<<endl;
				Vihecle2.hienthiVihecle();
				found = true;
			}
			
			else if(hasVihecle3 && Vihecle3.getvihecleType() == type){
				cout<<"Tim thay tai bai co ID: "<<parkID<<endl;
				Vihecle3.hienthiVihecle();
				found = true;
			}
		}
		
		void xoaLot(){
			parkID = -1;
			size = 'S';
			hasVihecle1 = false;
			hasVihecle2 = false;
			hasVihecle3 = false;
			isExist = false;
			Vihecle1 = Vihecle();
			Vihecle2 = Vihecle();
			Vihecle3 = Vihecle();
		}	
};

class SystemInterface{
	private:
		parkingLot parkingLot1, parkingLot2, parkingLot3;
		bool hasLot1, hasLot2, hasLot3;
		
		bool trunglapLot(int id){
			if(hasLot1 && parkingLot1.getparkID() == id) return true;
			if(hasLot2 && parkingLot2.getparkID() == id) return true;
			if(hasLot3 && parkingLot3.getparkID() == id) return true;
			return false;
		}
		
		bool trunglapVihecle(int id){
			if(hasLot1 && parkingLot1.coVihecleko(id) == id) return true;
			if(hasLot2 && parkingLot2.coVihecleko(id) == id) return true;
			if(hasLot3 && parkingLot3.coVihecleko(id) == id) return true;
			return false;
		}
	public:
		SystemInterface(){
			hasLot1 = false;
			hasLot2 = false;
			hasLot3 = false;
		}
		void hienthimenu(){
			int luachon;
			do{
				cout<<"1. Tao bai do xe moi"<<endl;
				cout<<"2. Them xe vao bai do"<<endl;
				cout<<"3. Xoa mot bai do xe"<<endl;
				cout<<"4. Lay xe khoi bai"<<endl;
				cout<<"5. Hien thi tat ca bai do xe"<<endl;
				cout<<"6. Hien thi danh sach xe theo bai"<<endl;
				cout<<"7. Liet ke xe theo loai"<<endl;
				cout<<"8. Xem bao cao tom tat chi phi"<<endl;
				cout<<"9. Thoat chuong trinh"<<endl;
				cout<<"Moi ban nhap lua chon (1-9): ";
				cin>>luachon;
				
				switch(luachon){
					case 1:
						taobaido();
						break;
					case 2:	
						themxe();
						break;
					case 3:
						xoabaido();
						break;
					case 4:
						layxe();
						break;
					case 5:
						hienthitatcaibaido();
						break;
					case 6:
						hienthidanhsachxe();
						break;
					case 7:
						lietke();
						break;
					case 8:
						xembaocao();
						break;
					case 9:
						cout << "Cam on ban da su dung he thong. Tam biet!"<<endl;
						break;	
				}
			}while(luachon != 9);
		}
	private:
		void taobaido(){
			if(hasLot1 && hasLot2 && hasLot3){
				cout<<"Da du so luong bai xe (toi da 3 bai)"<<endl;
			}
			int pID;
			char size;
			cout<<"Moi ban nhap ma bai do: ";
			cin>>pID;
			if(trunglapLot(pID)){
				cout<<"Loi: Ma bai xe da ton tai"<<endl;
				return;
			}
			cout<<"Moi ban nhap kich thuoc bai:";
			cin>>size;
			size = toupper(size);
			if(size != 'S' || size != 'M' || size != 'L'){
				cout<<"Loi: Ban da nhap sai dinh dang size bai"<<endl;
				return;
			}
						
			if(hasLot1 == false){
				parkingLot1 = parkingLot(pID, size);
				hasLot1 = true;
			}
			else if(hasLot2 == false){
				parkingLot2 = parkingLot(pID, size);
				hasLot2 = true;
			}
			else if(hasLot3 == false){
				parkingLot3 = parkingLot(pID, size);
				hasLot3 = true;
			}
						
			cout<<"Tao bai xe thanh cong"<<endl;
		}
		
		void themxe(){
	        if (!hasLot1 && !hasLot2 && !hasLot3) {
	            cout << "Chua co bai do xe nao trong he thong. Vui long tao bai truoc"<<endl;
	            return;
	        }
	
	        int vID, entryTime, duration;
	        string vType;
	
	        cout << "Nhap ma xe: ";
	        cin >> vID;
	
	        if (trunglapVihecle(vID)) {
	            cout << "Loi: Ma xe da ton tai trong he thong!"<<endl;
	            return;
	        }
	
	        cout << "Nhap loai xe: ";
	        cin >> vType;
	
	        cout << "Nhap gio vao bai (0 - 23): ";
	        cin >> entryTime;
	        if (entryTime < 0 || entryTime > 23) {
	            cout << "Loi: Gio vao phai tu 0 den 23"<<endl;
	            return;
	        }
	
	        cout << "Nhap thoi luong do du kien (1 - 23 gio): ";
	        cin >> duration;
	        if (duration < 1 || duration > 23) {
	            cout << "Loi: Thoi luong do phai tu 1 den 23"<<endl;
	            return;
	        }
	
	        Vihecle newVihecle = Vihecle(vID, vType, entryTime, duration);
	        
	        bool added = false;
	        if (hasLot1 && parkingLot1.addVihecle(newVihecle)) {
	            added = true;
	            cout << "Them xe thanh cong vao Bai ID: " << parkingLot1.getparkID() <<endl;
	        } else if (hasLot2 && parkingLot2.addVihecle(newVihecle)) {
	            added = true;
	            cout << "Them xe thanh cong vao Bai ID: " << parkingLot2.getparkID() <<endl;
	        } else if (hasLot3 && parkingLot3.addVihecle(newVihecle)) {
	            added = true;
	            cout << "Them xe thanh cong vao Bai ID: " << parkingLot3.getparkID() <<endl;
	        }
	
	        if (!added) {
	            cout << "Loi: Tat ca cac bai do xe hien tai da day cho"<<endl;
	        }
	    }
	    
	    void xoabaido() {
	        if (!hasLot1 && !hasLot2 && !hasLot3) {
	            cout << "Khong co bai do xe nao trong he thong"<<endl;
	            return;
	        }
	
	        int pID;
	        cout << "Nhap ma bai do can xoa: ";
	        cin >> pID;
	
	        bool removed = false;
	        if (hasLot1 && parkingLot1.getparkID() == pID) {
	            if (parkingLot1.demVihecle() > 0) {
	                cout << "Loi: Khong the xoa vi bai do van con xe ben trong"<<endl;
	                return;
	            }
	            parkingLot1.xoaLot();
	            hasLot1 = false;
	            removed = true;
	        } else if (hasLot2 && parkingLot2.getparkID() == pID) {
	            if (parkingLot2.demVihecle() > 0) {
	                cout << "Loi: Khong the xoa vi bai do van con xe ben trong"<<endl;
	                return;
	            }
	            parkingLot2.xoaLot();
	            hasLot2 = false;
	            removed = true;
	        } else if (hasLot3 && parkingLot3.getparkID() == pID) {
	            if (parkingLot3.demVihecle() > 0) {
	                cout << "Loi: Khong the xoa vi bai do van con xe ben trong"<<endl;
	                return;
	            }
	            parkingLot3.xoaLot();
	            hasLot3 = false;
	            removed = true;
	        }
	
	        if (removed) {
	            cout << "Xoa bai do xe thanh cong"<<endl;
	        } else {
	            cout << "Loi: Không tim thay ma bai do nay"<<endl;
	        }
	    }

	    void layxe() {
	        int vID;
	        cout << "Nhap ma xe can lay ra: ";
	        cin >> vID;
	
	        bool removed = false;
	        if (hasLot1 && parkingLot1.removeVihecle(vID)) {
	            removed = true;
	        } 
			else if (hasLot2 && parkingLot2.removeVihecle(vID)) {
	            removed = true;
	        } 
			else if (hasLot3 && parkingLot3.removeVihecle(vID)) {
	            removed = true;
	        }
	
	        if (removed) {
	            cout << "Lay xe ra khoi bai do thanh cong"<<endl;
	        } 
			else {
	            cout << "Loi: Không tim thay xe co ma nay trong he thong"<<endl;
	        }
	    }
	    
	    void hienthitatcaibaido() {
	        if (!hasLot1 && !hasLot2 && !hasLot3) {
	            std::cout << "He thong chua co bai do xe nao"<<endl;
	            return;
	        }
	        cout <<"Danh sach sac bai do:"<<endl;
	        if (hasLot1) parkingLot1.hienthiLot();
	        if (hasLot2) parkingLot2.hienthiLot();
	        if (hasLot3) parkingLot3.hienthiLot();
    	}
    	
    	void hienthidanhsachxe(){
	        if (!hasLot1 && !hasLot2 && !hasLot3) {
	            cout << "He thong chua co bai do xe nao"<<endl;
	            return;
	        }
	
	        int pID;
	        cout << "Nhap ma bai do: ";
	        cin >> pID;
	
	        if (hasLot1 && parkingLot1.getparkID() == pID) {
	            parkingLot1.hienthithongtinLot();
	        } 
			else if (hasLot2 && parkingLot2.getparkID() == pID) {
	            parkingLot2.hienthithongtinLot();
	        } 
			else if (hasLot3 && parkingLot3.getparkID() == pID) {
	            parkingLot3.hienthithongtinLot();
	        } 
			else {
	            cout << "Loi: Khong tim thay bai do xe nay"<<endl;
	        }
    	}
    	
    	void lietke(){
	        string type;
	        cout << "Nhap loai xe can liet ke: ";
	        cin >> type;
	
	        cout <<"Danh sach xe theo loai:"<< type <<endl;
	        bool found = false;
	        if (hasLot1) parkingLot1.timtheoType(type, found);
	        if (hasLot2) parkingLot2.timtheoType(type, found);
	        if (hasLot3) parkingLot3.timtheoType(type, found);
	
	        if (!found) {
	            cout << "Khong tim thay xe nao thuoc loai nay trong he thong"<<endl;
	        }
    	}
    	
    	void xembaocao(){
        cout << "Bao cao do xe: "<<endl;
        
        string types[3] = {"Car", "Motorcycle", "Bicycle"};
        
        for (int i = 0; i < 3; ++i) {
            double totalFeeAll = 0.0;
            int totalCountAll = 0;

            if (hasLot1) parkingLot1.baocao(types[i], totalFeeAll, totalCountAll);
            if (hasLot2) parkingLot2.baocao(types[i], totalFeeAll, totalCountAll);
            if (hasLot3) parkingLot3.baocao(types[i], totalFeeAll, totalCountAll);

            cout <<"Loai xe" << types[i] <<endl;
            if (totalCountAll > 0) {
                cout << "Phi trung binh toan he thong: VND" << (totalFeeAll / totalCountAll) <<endl;
            } else {
                cout << "Phi trung binh toan he thong: 0VND (Chua co du lieu)"<<endl;
            }
        }
    }
};

int main() {
    SystemInterface systemInterface;
    systemInterface.hienthimenu();
    return 0;
}
