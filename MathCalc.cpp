#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <limits>
#include <cmath>
#include <map>
#include <string>
#include <windows.h>
using namespace std;
void color_red() {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, 12);
}
void color_white() {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color, 7 );
}
void color_green() {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color, 10 );
}
void cantitativ_variante() {
    system("CLS");
    cout<<"Rezolvare: Grupare cantitativa pe variante."<<endl<<endl;
    int n;
c9:
    cout << "Introduceti volumul: ";
    cin >> n;
    if(cin.fail()|| n<=0) {
        color_red();
        cout << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto c9;
    }
    double x[n]; // Tablou xi
    vector<double> xi;
    int count;
    bool found;
    for(int i = 0; i < n; i++) {
c8:
        cout << "Introduceti varianta [" << i + 1 << "]: ";
        cin >> x[i];
        found = false;
        for(int j = 0; j < xi.size(); j++) {
            if(x[i] == xi[j]) {
                found = true;
                break;
            }
        }
        if(!found) {
            xi.push_back(x[i]);
        }
        if(cin.fail()) {
            color_red();
            cout << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto c8;
        }
    }
    // Ordonam crescator valorile din tabloul xi
    sort(xi.begin(), xi.end());
    double ni[xi.size()];
    for (int i = 0; i < xi.size(); i++) {
        count = 0;
        for(int j = 0; j < n; j++) {
            if(x[j] == xi[i]) {
                count++;
            }
        }
        ni[i] = count;
    }

    double fi[xi.size()];
    for (int i = 0; i < xi.size(); i++) {
        fi[i] = ni[i] / (double)n; // calculam fi pentru fiecare valoare
    }

    double Fi[xi.size()];
    Fi[0] = ni[0];
    for (int i = 1; i < xi.size(); i++) {
        Fi[i] = Fi[i - 1] + ni[i]; // calculam Fi pentru fiecare valoare
    }

    double FRC[xi.size()];
    FRC[0] = fi[0];
    for (int i = 1; i < xi.size(); i++) {
        FRC[i] = FRC[i - 1] + fi[i]; // calculam FRC pentru fiecare valoare
    }


    vector<double> mo;
    double temp1 =0;
    for(int i =0; i<xi.size(); i++) {
        if(ni[i] >= temp1) {
            temp1=ni[i];
        }
    }



    cout << "Grupare pe variante: " << endl << endl;
    cout << "xi\tni\tFi\tfi\tFRC\t" << endl;
    int z=0;
    for (int i = 0; i < xi.size(); i++) {
        z++;
        cout<< xi[i] << "\t" << ni[i] << "\t" << Fi[i] << "\t" << fixed<<setprecision(3)<< fi[i] << "\t" << FRC[i] <<"\t"<< endl<<fixed<<setprecision(0);
    }

    double mediana = (n+1)/2.0, Fii, xii;
    for(int i=0; i<z; i++) {
        if(Fi[i] > mediana) {
            Fii = Fi[i];
            xii = xi[i];
            break;
        }
    }

    double x1 = 0, d = 0, temp = 0;
    for(int i = 0; i < z; i++) {
        temp = xi[i] * ni[i];
        d += temp;
        temp = 0;
    }
    x1 = d/n;


    cout<<endl<<"Media aritetica:"<<fixed<< setprecision(3)<<x1<<endl;
    cout<<"Me: Fi>"<<mediana<<" => Fi="<<Fii<<" => xi= "<<xii<<fixed<< setprecision(0)<<endl;
    cout<<"Mo: ni_max = "<<temp1<<" => ";
    for(int i =0; i<xi.size(); i++) {
        if(ni[i]==temp1) {
            cout<<"xi = "<<xi[i]<<"; ";
        }
    }

    cout<<endl<<endl<<"M->101?";
}
void cantitativ_intervale() {
    system("CLS");
    cout<<"Rezolvare: Grupare cantitativa pe intervale."<<endl<<endl;
    int z = 0;
    int n;
    double ME = 0;
    double mediana =0;
    double FME = 0;
    double NME=0 ;
    double limit_min;
    cout << "Introduceti volumul: ";
    cin >> n;

    double x[n]; // Tablou xi
    vector<double> unique_x;
    int count;
    int temp;
    bool found;
    for(int i = 0; i < n; i++) {
c8:
        cout << "Introduceti elementul [" << i + 1 << "]: ";
        cin >> x[i];

        found = false;
        for(int j = 0; j < unique_x.size(); j++) {
            if(x[i] == unique_x[j]) {
                found = true;
                break;
            }
        }
        if(!found) {
            unique_x.push_back(x[i]);
        }
        if(cin.fail()) {
            color_red();
            cout << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto c8;
        }
    }

    // Ordonam crescator valorile din tabloul unique_x
    sort(unique_x.begin(), unique_x.end());

    double min_x = unique_x[0];
    double max_x = unique_x[unique_x.size() - 1];
    double r = 1 + 3.322*log10(n); // Formula lui Sturges
    double roundr = ceil(r);
    double h = (max_x - min_x) / roundr; // Marimea intervalului
    double roundh = ceil(h * 10.0) / 10.0; // rotunjire h

    // Calculam limitele intervalelor
    vector<double> interval_limits;
    interval_limits.push_back(min_x);
    for(int i = 1; i <= r; i++) {
        interval_limits.push_back(interval_limits[i - 1] + roundh);
    }
    double last_interval_limit = max_x + (roundr * roundh - (max_x - min_x));
    interval_limits.push_back(last_interval_limit);
    double ni[interval_limits.size() - 1];
    for(int i = 0; i < interval_limits.size() - 1; i++) {
        count = 0;
        for(int j = 0; j < n; j++) {
            if(x[j] >= interval_limits[i] && x[j] < interval_limits[i+1]) {
                count++;
            } else if(x[j] == interval_limits[i+1] && i+1 == interval_limits.size() - 1) {
                count++;
                ni[i+1] = count;
            }
        }
        ni[i] = count;
    }
    double fi[interval_limits.size() - 1];
    for(int i = 0; i < interval_limits.size() - 1; i++) {
        fi[i] = ni[i] / (double)n;
    }

    double Fi[interval_limits.size() - 1];
    Fi[0] = ni[0];
    for(int i = 1; i < interval_limits.size() - 1; i++) {
        Fi[i] = Fi[i-1] + ni[i];
    }

    double FRC[interval_limits.size() - 1];
    FRC[0] = fi[0];
    for(int i = 1; i < interval_limits.size() - 1; i++) {
        FRC[i] = FRC[i-1] + fi[i];
    }

    mediana = (n+1)/2.0;
    for(int i = 0; i < n; i++) {
        if(Fi[i] > mediana) {
            FME = Fi[i-1];
            limit_min = interval_limits[i];
            NME = ni[i];
            break;
        }
    }
    ME =limit_min + (roundh *(((mediana-FME)/NME)));
    // output the cumulative frequency table
    cout<<endl;
    cout << "Grupare pe intervale: " << endl;
    cout<<endl;
    cout << "N\tIntervale\txi*\tni\tFi\tfi\tFRC" << endl;
    for(int i = 0; i < interval_limits.size() - 1; i++) {
        z++;
        double xxi = (interval_limits[i] + interval_limits[i+1]) / 2;
        cout <<""<<z<<"\t" <<"[" << fixed << setprecision(2) << interval_limits[i] << ", " << interval_limits[i+1] << ")\t" <<""<<fixed << setprecision(1)<<xxi<<"\t"<< ni[i] << "\t" << Fi[i]<< "\t" << fixed << setprecision(2) << fi[i] << "\t" << FRC[i] << endl;
    }
    double xi[interval_limits.size()- 1];
    for(int i = 0; i < z; i++) {
        xi[i] = (interval_limits[i] + interval_limits[i+1]) / 2;
    }

    double x1 = 0, d = 0, temp1 = 0;
    for(int i = 0; i < z; i++) {
        temp1 = xi[i] * ni[i];
        d += temp1;
        temp1 = 0;
    }
    x1 = d/n;



    cout<<endl;
    cout<<"r = 1+3.322lg"<<n<<" = "<<""<<r<<" => r = "<<fixed<<setprecision(0)<<roundr<<endl;

    cout<<"h = ("<<max_x<<" - "<<min_x<<") / "<<roundr<<" = "<<fixed<<setprecision(2)<<h<<" => h = "<<fixed<<setprecision(2)<<roundh<<endl;

    cout<<"Med.arit = "<<fixed<<setprecision(2)<< x1<<endl;

    cout<<"Me = "<<limit_min<<" + ("<<roundh<<" *(("<<mediana<<"-"<<FME<<")/"<<NME<<"))) = "<<ME<<endl;

    vector<double> mo;
    double temp2;
    for(int i = 0; i< z; i++) {
        if(ni[i] >= temp2) {
            temp2=ni[i];
        }
    }
    cout<<"Mo: ni_max = "<<temp2<<" => ";
    double limit_min1, limit_max1;
    int n01, n02, n03;
    for(int i =0; i< z; i++) {
        if(ni[i]== temp2) {
            n01=ni[i-1];
            n02=ni[i];
            n03=ni[i+1];
            cout<<"xi = "<<fixed<<setprecision(2)<<xi[i]<<fixed<<setprecision(2)<<endl;
            limit_min1=interval_limits[i];
            limit_max1=interval_limits[i+1];
            break;
        }
    }
    double Mo1;
    Mo1= limit_min1 + ((roundh *(n02-n01))/(n02-n01+(n02-n03)));
    cout<<endl;
    cout<<"Intervalul modului:"<<endl<<"x_inf = "<<limit_min1<<endl<<"x_sup = "<<limit_max1<<endl<<"h = "<<roundh<<endl<<"n1 = "<<n01<<endl<<"n2 = "<< n02<<endl<< "n3 = "<< n03<<endl<<"Mo = "<<limit_min1<< " + ("<<roundh<<"* (("<<n02<<" - "<<n01<<")/("<<n02<<" - "<< n01<<" + ("<<n02<<" - "<< n03<<")))) = "<<Mo1<<endl;
    cout<<endl<<endl<<"M->101?";
}
void calitativ_variante() {
    system("CLS");
    cout<<"Rezolvare: Grupare calitativa pe variante."<<endl<<endl;
    int n;
c8:
    cout << "Introduceti volumul: ";
    cin >> n;
    if(cin.fail()) {
        color_red();
        cout << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto c8;
    }
    map<string, int> wordCount;
    string word;
    for (int i = 0; i < n; i++) {
c10:
        cout << "Introduceti cuvantul " << i+1 << ": ";
        cin >> word;
        // Verificare daca cuvantul contine cifre
        bool hasDigits = false;
        for (char c : word) {
            if (isdigit(c)) {
                hasDigits = true;
                break;
            }
        }
        // Daca cuvantul contine cifre, afisam un mesaj de eroare si cerem introducerea din nou
        if (hasDigits) {
            cout << "Valoare invalida. Introduceti un cuvant fara cifre.\n";
            goto c10;
        }
        wordCount[word]++;
    }

    int numWords = wordCount.size();
    string words[numWords];
    int ni[numWords];

    // Umplem array-urile cu valorile corespunzatoare
    int index = 0;
    for (auto& x : wordCount) {
        words[index] = x.first;
        ni[index] = x.second;
        index++;
    }

    // Calculam valorile Fi
    double Fi[numWords];
    Fi[0] = ni[0];
    for(int i = 1; i < numWords; i++) {
        Fi[i] = Fi[i-1] + ni[i];
    }

    // Calculam valorile fi
    double fi[numWords];
    for(int i = 0; i < numWords; i++) {
        fi[i] = ni[i] / (double)n;
    }

    // Calculam valorile FRC
    double FRC[numWords];
    FRC[0] = fi[0];
    for(int i = 1; i < numWords; i++) {
        FRC[i] = FRC[i-1] + fi[i];
    }

    // Afisam tabelul cu toate valorile

    cout <<endl<< "Grupare pe variante: " << endl << endl;
    cout << left << setw(15) << "xi" << setw(10) << "ni" << setw(10) << "Fi" << setw(10) << "fi" << setw(10) << "FRC" << endl;
    for (int i = 0; i < numWords; i++) {
        cout << left << setw(15)<< words[i] << setw(10) << ni[i] << setw(10) << fixed << setprecision(0) <<Fi[i] << setw(10) << fixed << setprecision(3) << fi[i] << setw(10) << FRC[i] << endl;
    }

    vector<double> mo;
    double temp1 =0;
    for(int i =0; i<numWords; i++) {
        if(ni[i] >= temp1) {
            temp1=ni[i];
        }
    }
    cout<<endl<<"Mo: ni_max = "<<temp1<<" => ";
    for(int i =0; i< numWords; i++) {
        if(ni[i]==temp1) {
            cout<<"xi = "<<words[i]<<"; ";
        }
    }
    cout<<endl<<endl<<"M->101?";
}
void Salariu_Brut() {
    double Sb = 0, CAM = 0, Imv = 0, P= 0, Snet = 0, CAS = 0;
    int Anual = 0;
    system("CLS");
    cout<<"Rezolvare: Salariul brut."<<endl<<endl;
a1:
    cout << "Introduceti salariul Brut:";
    cin >> Sb;
    if (cin.fail()|| Sb<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
    system("CLS");
    cout << "Se da:" << endl << endl << "Sb = " << Sb << " Lei";
    // Formule
    CAM = Sb * 0.09;//CAM
    Anual = Sb * 12;//Anual
    cout << endl << "----------------------" << endl << "       Rezolvare" << endl << endl;
    //Rezolvare
    cout <<fixed << setprecision(2)<< "1) CAM = " << Sb << " Lei * 9% = " << CAM << " Lei";//CAM afisare
    if (Sb<=4600 || Anual >= 360000) {
        Imv = Sb * 0.12;
        cout << endl << endl << "2) Imv = " << Sb << " Lei * 12% = " << Imv << " Lei";
    } else {
        Imv = (Sb - 2250)*0.12;
        cout << endl << endl << "2) Imv = " << "("<< Sb << " Lei - 2250 Lei) * 12% = " << Imv << " Lei";
    }
    //Formula P
    P = CAM + Imv;
    //Rezolvare
    cout << endl << endl << "3) P = " << CAM << " Lei + " << Imv << " Lei = " << P << " Lei";
    //Formule
    Snet = Sb - P;
    cout << endl << endl << "4) Snet = " << Sb << " Lei - " << P << " Lei = " << Snet << " Lei";
    //Formule
    CAS = Sb * 0.24;
    //Rezolvare
    cout << endl << endl << "5) CAS = " << Sb << " Lei * 24% = " << CAS << " Lei";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void FsAA() {

    int num, nrpers = 0;
    double Fsm = 0,Fsa=0, Fsl = 0, CASl = 0, CASa = 0, Ch = 0, Fsaa = 0;
    system("CLS");
    cout<<"Rezolvare: Fond de salarizare anual(Fsa)."<<endl<<endl;
a1:
    cout << "Introduceti numarul de functi:";
    cin >> num;
    if (cin.fail()|| num<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
    string nm[num];
    double money[num];
    int nr[num];
    for (int i = 0; i < num; i++) {
a2:
        cout << endl<< "Introdu numele functiei, salariul, nr agajati"<< endl;
        cout << i+1<< ") ";
        cin >> nm[i];
        if (cin.fail()) {
            color_red();
            cout << endl << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto a2;
        }
        cout << i+1<< ") ";
        cin >> money[i];
        if (cin.fail()|| money[i]<=0) {
            color_red();
            cout << endl << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto a2;
        }

        cout << i+1<< ") ";
        cin >> nr[i];
        if (cin.fail()|| nr[i]<=0) {
            color_red();
            cout << endl << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto a2;
        }
    }
    system("CLS");
    cout << "Se da:" << endl << endl;
    for (int j = 0; j < num; j++) {
        cout  << j+1 << ") " << nm[j] << " - " << money[j] << " Lei - " << nr[j] << endl;
    }
    cout << "-------------------------"<< endl << "            Rezolvare";
    cout  <<fixed << setprecision(2)<< endl << endl << "1) Fsm = 0";
    for (int h = 0; h < num; h++) {
        Fsm = Fsm + (money[h] * nr[h]);
        nrpers = nrpers + nr[h];
    }
    Fsm = Fsm / nrpers;
    for (int d = 0; d < num; d++) {
        cout << " + "<< nr[d] << " * " << money[d]<< " Lei";
    }
    cout << " / " << nrpers << " = " << Fsm << " Lei" ;
    Fsl = nrpers * Fsm;
    cout << endl << endl << "2) Fsl = " << nrpers << " * " << Fsm << " Lei = " << Fsl << " Lei";
    Fsa = Fsl * 12;
    cout << endl << endl << "3) Fsa = " << Fsl << " Lei" << " * " << 12 << " = " << Fsa << " Lei";
    CASl = Fsl  * 0.24;
    cout << endl << endl << "4) CASl = " << Fsl << " Lei" << " * " << "24% = " << CASl << " Lei";
    CASa = CASl * 12;
    cout << endl << endl << "5) CASa = " << CASl << " Lei" << " * " << 12 << " = " << CASa << " Lei";
    Ch = Fsl + CASl;
    cout << endl << endl << "6) Ch = " << Fsl << " Lei" << " + " << CASl << " Lei = " << Ch << " Lei";
    Fsaa = Ch * 12;
    cout << endl << endl << "7) Fsaa = " << Ch << " Lei" << " * " << 12 << " = " << Fsaa << " Lei";
    cout<<endl<<endl<<"M->101?";
}
void VV() {

    double Vv = 0, At=0, Cp = 0, Vi = 0, Pnet = 0, Pb = 0, Rf = 0, Re = 0, Rv = 0, P = 0;
    system("CLS");
    cout<<"Rezolvare: Eficienta economica."<<endl<<endl;
    //Introducerea datelor
a1:
    cout << "Introduceti Venitul pe Vanzari:";
    cin  >> Vv;
    if (cin.fail()|| Vv<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti Active Totale:";
    cin >> At;
    if (cin.fail()|| At<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
a3:
    cout << "Introduceti Capitalul Propriu:";
    cin >> Cp;
    if (cin.fail()|| Cp<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a3;
    }
    system("CLS");
    //Afiseaza datele problemei
    cout << "Se da:" << endl << endl;
    cout << "Vv = " << Vv << " Lei" << endl;
    cout << "At = " << At << " Lei" << endl;
    cout << "Cp = " << Cp << " Lei" << endl;
    //Rezolvare
    cout << "-------------------------"<< endl << "            Rezolvare";
    //Formule
    Vi = Vv - (At - Cp);
    cout <<fixed << setprecision(2)<< endl << endl << "1) Vi = " << Vv << " Lei - (" << At << " Lei - " << Cp << " Lei) = " << Vi << " Lei";
    P = Vi * 0.12;
    cout << endl << endl << "2) P = " << Vi << " Lei * 12% = " << P << " Lei";
    Pnet = Vv - P;
    cout << endl << endl << "3) Pnet = " << Vv << " Lei - " << P << " Lei = " << Pnet << " Lei";
    Pb = Vv - At;
    cout << endl << endl << "4) Pb = " << Vv << " Lei - " << At << " Lei = " << Pb << " Lei";
    Rf = Pnet / Cp;
    cout<< fixed << setprecision(2)  << endl << endl << "5) Rf = " << Pnet << " Lei / " << Cp << " Lei = " << fixed << setprecision(3) <<  Rf << " %";
    Re = Pnet / At;
    cout<< fixed << setprecision(2)  << endl << endl << "6) Re = " << Pnet << " Lei / " << At << " Lei = " << fixed << setprecision(3) << Re << " %";
    Rv = Pb / Vv;
    cout<< fixed << setprecision(2)  << endl << endl << "7) Rv = " << Pb << " Lei / " << Vv << " Lei = " << fixed << setprecision(3) << Rv << " %";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void profit() {

    double pr = 0, v=0, prbuc=0, q=0, p=0, cm=0, ct=0, cs=0, ctm=0, prbuc1 =0;
    system("CLS");
    cout<<"Rezolvare: Profit."<<endl<<endl;
    //Introducerea datelor
a1:
    cout << "Introduceti Cm:";
    cin  >> cm;
    if (cin.fail()|| cm<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti Cs:";
    cin >> cs;
    if (cin.fail()|| cs<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
a3:
    cout << "Introduceti Q:";
    cin >> q;
    if (cin.fail()|| q<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a3;
    }
a4:
    cout << "Introduceti P:";
    cin >> p;
    if (cin.fail()|| p<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a4;
    }
    system("CLS");
    //Afiseaza datele problemei
    cout << "Se da:" << endl << endl;
    cout << "Cm = " << cm << " Lei" << endl;
    cout << "Cs = " << cs << " Lei" << endl;
    cout << "Q = " << q << " buc" << endl;
    cout << "P = " << p<< " Lei " << endl;
    //Rezolvare
    cout << "-------------------------"<< endl << "            Rezolvare";
    //Formule
    ct=cm+cs;
    cout <<fixed << setprecision(3)<< endl << endl << "1) Ct = " << cm << " Lei + " << cs << " Lei = " << ct << " Lei";
    v= q*p;
    cout << endl << endl << "2) V= " << q << " Lei *"<<p <<"Lei= "<< v << " Lei";
    pr= v - ct;
    cout << endl << endl << "3) Pr = "<< v << " Lei - " << ct << " Lei = " << pr << " Lei";
    prbuc = pr/q;
    cout<< fixed << setprecision(3) << endl << endl << "4) Prbuc = " << pr << " Lei / " << q << " buc = " << fixed << setprecision(3) << prbuc << " Lei/buc";
    ctm= ct/q;
    cout<< fixed << setprecision(3) << endl << endl << "5) CTM = " << ct << " Lei / " << q << " buc = " << fixed << setprecision(3) << ctm << " Lei/buc";
    prbuc1= p-ctm;
    cout<< fixed << setprecision(3) << endl << endl << "6) Prbuc = " << p<< " Lei - " << ctm << " Lei/buc = " << fixed << setprecision(3) << prbuc1 << " Lei/buc";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void Reducere() {
    system("CLS");
    cout<<"Rezolvare: Reducere(a - b% = x)."<<endl<<endl;
    double a, b, x;
a1:
    cout << "Introduceti numarul A:";
    cin >> a;
    if (cin.fail()|| a<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti procentajul B:";
    cin >> b;
    if (cin.fail()|| b<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
    system("CLS");
    cout << "Se da:" << endl << endl << "A = " << a <<" u.m."<<endl<<"B = " << b <<" %";
    // Formule
    x = a-((a*b)/100);
    cout << endl << "----------------------" << endl << "       Rezolvare" << endl << endl;
    //Rezolvare
    cout <<fixed << setprecision(2)<< "Reducere = " << a << " - (" << a << " * "<<b<<"%)/100 = "<<x<<" u.m.";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void Marire() {
    system("CLS");
    cout<<"Rezolvare: Marire(a + b% = x)."<<endl<<endl;
    double a, b, x;
a1:
    cout << "Introduceti numarul A:";
    cin >> a;
    if (cin.fail()|| a<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti procentajul B:";
    cin >> b;
    if (cin.fail()|| b<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
    system("CLS");
    cout << "Se da:" << endl << endl << "A = " << a <<" u.m."<<endl<<"B = " << b <<" %";
    // Formule
    x = a+((a*b)/100);
    cout << endl << "----------------------" << endl << "       Rezolvare" << endl << endl;
    //Rezolvare
    cout <<fixed << setprecision(2)<< "Marire = " << a << " + (" << a << " * "<<b<<"%)/100 = "<<x<<" u.m.";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void Procent_simplu() {
    system("CLS");
    cout << "Rezolvare: Procent Simplu(a * b% = x)."<<endl<<endl;
    double a, b, x;
a1:
    cout << "Introduceti numarul A:";
    cin >> a;
    if (cin.fail()|| a<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti procentajul B:";
    cin >> b;
    if (cin.fail()|| b<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
    system("CLS");
    cout << "Se da:" << endl << endl << "A = " << a <<" u.m."<<endl<<"B = " << b <<" %";
    // Formule
    x = a*b/100;
    cout << endl << "----------------------" << endl << "       Rezolvare" << endl << endl;
    //Rezolvare
    cout <<fixed << setprecision(2)<< "Procent simplu = " << a << " * " << b << "%/100 = "<<x<<" u.m.";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void marimea_g() {
    system("CLS");
    cout << "Rezolvare: Marimea initiala (a / b% = x)."<<endl<<endl;
    double a, b, x;
a1:
    cout << "Introduceti numarul A:";
    cin >> a;
    if (cin.fail()|| a<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti procentajul B:";
    cin >> b;
    if (cin.fail()|| b<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
    system("CLS");
    cout << "Se da:" << endl << endl << "A = " << a <<" u.m."<<endl<<"B = " << b <<" %";
    // Formule
    x = (a/b)*100;
    cout << endl << "----------------------" << endl << "       Rezolvare" << endl << endl;
    //Rezolvare
    cout <<fixed << setprecision(2)<< "Marimea initiala = (" << a << " / " << b << ") * 100 = "<<x<<" u.m.";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void Marire_Scadere() {
    system("CLS");
    cout << "Rezolvare: Procentul taxelor (a -> b = x%)."<<endl<<endl;
    double a, b, x;
a1:
    cout << "Introduceti numarul A:";
    cin >> a;
    if (cin.fail()|| a<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti numarul B:";
    cin >> b;
    if (cin.fail()|| b<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
    system("CLS");
    cout << "Se da:" << endl << endl << "A = " << a <<" u.m."<<endl<<"B = " << b <<" u.m.";
    // Formule
    x = ((b*100)/a)-100;
    cout << endl << "----------------------" << endl << "       Rezolvare" << endl << endl;
    //Rezolvare
    cout <<fixed << setprecision(2)<< "Procentul taxelor= ((" << b << " * 100)/"<<a<<") - " << b << " = "<<x<<" %";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void Procent_A_B() {
    system("CLS");
    cout << "Rezolvare: Procentul lui A din B(a <- b = x%)."<<endl<<endl;
    double a, b, x;
a1:
    cout << "Introduceti numarul A:";
    cin >> a;
    if (cin.fail()|| a<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti numarul B:";
    cin >> b;
    if (cin.fail()|| b<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
    system("CLS");
    cout << "Se da:" << endl << endl << "A = " << a <<" u.m."<<endl<<"B = " << b <<" u.m.";
    // Formule
    x = a*100/b;
    cout << endl << "----------------------" << endl << "       Rezolvare" << endl << endl;
    //Rezolvare
    cout <<fixed << setprecision(2)<< "Procentul lui A din B = " << a << " * " << "100%/"<<b<<" = "<<x<<"%";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void Dobanda_simpla() {
    system("CLS");
    cout << "Calculare: Dobanda simpla."<<endl<<endl;
    double p, so, ds=0, t;
    int n;
    string mas, mas1;
a1:
    cout << "Introduceti suma initiala:";
    cin >> so;
    if (cin.fail()|| so<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti procentul:";
    cin >> p;
    if (cin.fail()|| p<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
    double p2;
    p2=p/100;
a4:
a3:
    cout << "Specificati unitatea de masura a timpului: ";
    cout << endl << endl << "1) Ani";
    cout << endl << endl << "2) Luni";
    cout << endl << endl << "3) Zile";
    cout << endl << endl << "Operatia dvs. este: ";
    cin >>n;
    if (cin.fail()|| n<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a3;
    }

    if(n==1) {
        double ds_ani;
a5:
        cout << "Introduceti timpul in ani, t:";
        cin >> t;
        if (cin.fail()|| t<=0) {
            color_red();
            cout << endl << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto a5;
        }
        ds_ani = so*(1+(t*p2)/1);
        ds= ds_ani;
        mas = "a";
        mas1 ="100%";
    } else if (n==2) {
        double ds_luni;
a6:
        cout << "Introduceti timpul in luni, t:";
        cin >> t;
        if (cin.fail()|| t<=0) {
            color_red();
            cout << endl << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto a6;
        }
        ds_luni = so*(1+(t*p2)/12);
        ds = ds_luni;
        mas = "l";
        mas1 ="1200%";
    } else if (n==3) {
        double ds_zile;
a7:
        cout << "Introduceti timpul in zile, t:";
        cin >> t;
        if (cin.fail()|| t<=0) {
            color_red();
            cout << endl << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto a7;
        }
        ds_zile = so*(1+(t*p2)/360);
        ds = ds_zile;
        mas = "z";
        mas1 ="36000%";
    } else {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        goto a4;
    }

    system("CLS");
    cout << "Se da:" << endl << endl << "So = " << so <<" u.m." <<endl<<"T = " << t<< " "<<mas<<endl<<"P = "<<p<<" %";
    cout << endl << "----------------------" << endl << "       Rezolvare" << endl << endl;
    //Rezolvare
    cout <<fixed << setprecision(2)<< "DS = " << so << " * (" << "1 + (("<<t<<" * "<<p<<"%)/"<<mas1<<") = "<<setprecision(2)<<ds<<" u.m.";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void Dobanda_compusa() {
    system("CLS");
    cout << "Rezolvare: Dobanda compusa."<<endl<<endl;
    double p, so, dc=0, t;
    int n;
    string mas, mas1;
a1:
    cout << "Introduceti suma initiala:";
    cin >> so;
    if (cin.fail()|| so<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a1;
    }
a2:
    cout << "Introduceti procentul:";
    cin >> p;
    if (cin.fail()|| p<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a2;
    }
    double p2;
    p2=p/100;
a4:
a3:
    cout << "Specificati unitatea de masura a timpului: ";
    cout << endl << endl << "1) Ani";
    cout << endl << endl << "2) Luni";
    cout << endl << endl << "3) Zile";
    cout << endl << endl << "Operatia dvs. este: ";
    cin >>n;
    if (cin.fail()|| n<=0) {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto a3;
    }
    if(n==1) {
        double dc_ani;
a5:
        cout << "Introduceti timpul in ani, t:";
        cin >> t;
        if (cin.fail()|| t<=0) {
            color_red();
            cout << endl << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto a5;
        }
        dc_ani = so*pow(1+(p2/1), t);
        dc = dc_ani;
        mas = "a";
        mas1 ="100%";
    } else if (n==2) {
        double dc_luni;
a6:
        cout << "Introduceti timpul in luni, t:";
        cin >> t;
        if (cin.fail()|| t<=0) {
            color_red();
            cout << endl << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto a6;
        }
        dc_luni = so*pow(1+(p2/12), t);
        dc = dc_luni;
        mas = "l";
        mas1 ="1200%";
    } else if (n==3) {
        double dc_zile;
a7:
        cout << "Introduceti timpul in zile, t:";
        cin >> t;
        if (cin.fail()|| t<=0) {
            color_red();
            cout << endl << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto a7;
        }
        dc_zile = so*pow(1+(p2/360), t);
        dc = dc_zile;
        mas = "z";
        mas1 ="36000%";
    } else {
        color_red();
        cout << endl << "Valoare invalida!!!"<<endl<<endl;
        color_white();
        goto a4;
    }
    system("CLS");
    cout << "Se da:" << endl << endl << "So = " << so <<" u.m."<<endl<<"T = " << t<< " "<<mas<<endl<<"P = "<<p<<" %";
    cout << endl << "----------------------" << endl << "       Rezolvare" << endl << endl;
    //Rezolvare
    cout <<fixed << setprecision(2)<< "DC = " << so << " * (" << "1 + ("<<p<<"%/"<<mas1<<"))^"<<t<<" = "<<setprecision(2)<<dc<<" u.m.";
    cout << endl << "-----------------------------------";
    cout<<endl<<endl<<"M->101?";
}
void Devops() {
    system("CLS");
    cout<<"#############################################"<<endl;
    cout<<"#Congratulations You Have Found A Easter Egg#"<<endl;
    cout<<"#                                           #"<<endl;
    cout<<"#     Thank you for using this program <3   #"<<endl;
    cout<<"#      Devops: crystaL and Arcade_goooo     #"<<endl;
    cout<<"#                                           #"<<endl;
    cout<<"#         -Together We're Stronger-         #"<<endl;
    cout<<"#                                           #"<<endl;
    cout<<"#                                16/02/2023 #"<<endl;
    cout<<"#############################################"<<endl;
}
int main() {
    //Variabile
    char Key;
    int Operation;
    do {
        //Alege operatia
k1:
        cout << "Alegeti operatia dorita";
        cout << endl << endl << "1) Bazele antreprenoriatului";
        cout << endl << endl << "2) Elemente de calcul financiar";
        cout << endl << endl << "3) Elemente de statistica matematica"<<endl;
        cout << endl << endl << "Tastati 0 pentru a inchide programul";
        cout << endl << endl << "Operatia dvs. este: ";
        cin >> Operation;
        if (cin.fail()) {
            system("CLS");
            color_red();
            cout << "Valoare invalida!!!"<<endl<<endl;
            color_white();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto k1;
        }
        else if(Operation == 0) {
            system("CLS");
            color_green();
            cout<<"Programul a fost inchis";
            color_white();
            return 0;
        }
        system("CLS");
        //Check Operation
        if(Operation == 1) {
            do {
k2:
                cout << "Alegeti operatia dorita" << endl << endl;
                cout <<"1) Calculare Salariul Net";
                cout << endl << endl <<"2) Calculare Fond de salarizare anual(Fsa)";
                cout << endl << endl <<"3) Calculare Eficienta economica";
                cout << endl << endl <<"4) Calculare Profit"<<endl;
                cout << endl << endl << "Tastati 0 pentru a trece in meniul principal";
                cout << endl << endl << "Operatia dvs. este: ";
                cin >> Operation;
                if (cin.fail()) {
                    system("CLS");
                    color_red();
                    cout << "Valoare invalida!!!"<<endl<<endl;
                    color_white();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    goto k2;
                }
                else if(Operation == 0) {
                    system("CLS");
                    goto k1;
                }
                system("CLS");
                if(Operation == 1) {
                    do {
                        Salariu_Brut();
k3:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >>Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k3;
                        }
                        else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 2) {
                    do {
                        FsAA();
k4:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >>Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k4;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 3) {
                    do {
                        VV();
k5:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >>Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k5;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 4) {
                    do {
                        profit();
k6:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >>Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k6;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                }
            } while (Key == 'g' || Key == 'G');
        } else if(Operation == 2) {
            do {
k7:
                cout << "Alegeti operatia dorita";
                cout << endl << endl << "1) Calculare: Reducere";
                cout << endl << endl << "2) Calculare: Scumpire";
                cout << endl << endl << "3) Calculare: Procente p";
                cout << endl << endl << "4) Calculare: Procentajul lui A din B";
                cout << endl << endl << "5) Calculare: Dobanda simpla";
                cout << endl << endl << "6) Calculare: Dobanda compusa";
                cout << endl << endl << "7) Calculare: Procentul taxelor";
                cout << endl << endl << "8) Calculare: Marimea initiala";
                cout << endl << endl << "Tastati 0 pentru a trece in meniul principal";
                cout << endl << endl << "Operatia dvs. este: ";
                cin >> Operation;
                if (cin.fail()) {
                    system("CLS");
                    color_red();
                    cout << "Valoare invalida!!!"<<endl<<endl;
                    color_white();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    goto k7;
                }
                else if(Operation == 0) {
                    system("CLS");
                    goto k1;
                }
                system("CLS");
                if(Operation == 1) {
                    do {
                        Reducere();
k8:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >>Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k8;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 2) {
                    do {
                        Marire();
k9:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >>Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k9;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 3) {
                    do {
                        Procent_simplu();
k10:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >>Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k10;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 4) {
                    do {
                        Procent_A_B();
k11:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >> Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k11;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 5) {
                    do {
                        Dobanda_simpla();
k12:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >> Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k12;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 6) {
                    do {
                        Dobanda_compusa();
k13:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >> Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k13;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 7) {
                    do {
                        Marire_Scadere();
k19:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >> Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k19;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                } else if(Operation == 8) {
                    do {
                        marimea_g();
k20:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >> Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k20;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                }
            } while(Key == 'g' || Key == 'G');
        } else if(Operation == 3) {
            do {
k14:
                cout << "Alegeti operatia dorita";
                cout << endl << endl << "1) Caracteristica cantitativa";
                cout << endl << endl << "2) Caracteristica calitativa"<<endl;
                cout << endl << endl << "Tastati 0 pentru a trece in meniul principal";
                cout << endl << endl << "Operatia dvs. este: ";
                cin >> Operation;
                if (cin.fail()) {
                    system("CLS");
                    color_red();
                    cout << "Valoare invalida!!!"<<endl<<endl;
                    color_white();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    goto k14;
                }
                else if(Operation == 0) {
                    system("CLS");
                    goto k1;
                }
                system("CLS");
                if(Operation == 1) {
k15:
                    cout << "Alegeti operatia dorita";
                    cout << endl << endl << "1) Gruparea pe variante";
                    cout << endl << endl << "2) Gruparea pe intervale"<<endl;
                    cout << endl << endl << "Tastati 0 pentru a trece in submeniu";
                    cout << endl << endl << "Operatia dvs. este: ";
                    cin >> Operation;
                    if (cin.fail()) {
                        system("CLS");
                        color_red();
                        cout << "Valoare invalida!!!"<<endl<<endl;
                        color_white();
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        goto k15;
                    }
                    else if(Operation == 0) {
                        system("CLS");
                        goto k14;
                    }
                    if(Operation == 1) {
                        do {
                            cantitativ_variante();
k16:
                            cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";

                            cin >>Key;
                            if (cin.fail()) {
                                system("CLS");
                                color_red();
                                cout << "Valoare invalida!!!"<<endl<<endl;
                                color_white();
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                goto k16;
                            } else if (Key == 'e' || Key == 'E') {
                                system("CLS");
                                color_green();
                                cout<<"Programul a fost inchis";
                                color_white();
                                return 0;
                            }
                            system("CLS");
                        } while(Key == 'y' || Key == 'Y');
                    } else if(Operation == 2) {
                        do {
                            cantitativ_intervale();
k17:
                            cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                            cin >>Key;
                            if (cin.fail()) {
                                system("CLS");
                                color_red();
                                cout << "Valoare invalida!!!"<<endl;
                                color_white();
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                goto k17;
                            } else if (Key == 'e' || Key == 'E') {
                                system("CLS");
                                color_green();
                                cout<<"Programul a fost inchis";
                                color_white();
                                return 0;
                            }
                            system("CLS");
                        } while(Key == 'y' || Key == 'Y');
                    }
                } else if(Operation == 2) {
                    do {
                        calitativ_variante();
k18:
                        cout << endl << endl << "Tastati tasta m/M pentru meniul principal, tasta g/G pentru submeniu, tasta y/Y pentru a face recalcularea sau tastati e/E pentru a inchide programul: ";
                        cin >>Key;
                        if (cin.fail()) {
                            system("CLS");
                            color_red();
                            cout << "Valoare invalida!!!"<<endl<<endl;
                            color_white();
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            goto k18;
                        } else if (Key == 'e' || Key == 'E') {
                            system("CLS");
                            color_green();
                            cout<<"Programul a fost inchis";
                            color_white();
                            return 0;
                        }
                        system("CLS");
                    } while(Key == 'y' || Key == 'Y');
                }
            } while (Key == 'g' || Key == 'G');
        } else if(Operation == 101) {
            do {
                Devops();
                return 0;
            } while(Key == 'y' || Key == 'Y');
        }
        while(Key  == 'g' || Key == 'G');
    } while (Key == 'm' || Key == 'M');
    return 0;
}
