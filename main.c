#include <stdio.h>//girdi ve çıktı fonksiyonlarımız için
#include "OYUN.h"//prototipleri buraya kopyalıyoruz
struct yonelim{
    /* komutları algılayacak şekilde yapı belirliyoruz*/
    int yon;
    int kalem;
    int adim;
};
int main(){
    int a;
    printf("\a1->YENI OYUN\n2->ESKI OYUNU GORUNTULE\n");//bir harfe basılınca sonsuz döngüye giriyor
    scanf("%d",&a);
    switch (a) {
        /*seçmek istediği duruma göre yönlendirme yapıyoruz 1-->yeni oyun istenirse önce eski dosyayı sıfırlayıp
         kaçlık boyutta oynamak istediği alınıp komutların girileceği ekrana yönlendiriliyor,2-->eski oyunu görüntülemek ise
         yeni oyuna başlamadan önceki oynadığı son oyunu sonuçta bir dosyaya kaydediyoruz ve o dosyanın tekrar açılıp yazılması
         durumu oluyor,3-->son durumu kodu yazarken eksikleri net görebilmek için bazen sıfırlama işlemi yapıldığından oluşturdum,
         eğer bu üç sayı harici sayı girerse default oluyor ama şöyle bir durum var eğer yanlışlıkla bir harf girilirse sonsuz bir döngü
         içerisinde menüye dönüyor ve bu durumu önlemek için getch veya getchar kullanılabilir bu sefer ise bu fonksiyonlar girdiğiniz karakter
         ile birlikte enter tuşunu da depoladığı için iki defa menüdeki soru yöneltme durumunu yapıyor,açıkçası en iyi çözüm getchar ile yapmak gibi
         duruyor en azından ben öyle yapıyorum bu programda,belki başka bir menü oluşturup buraya aktarma yapınca düzelebilir bu durum ama ben bu şekilde
         bırakıyorum*/
        case 1:
            sifirlama();//oynamaya başlamadan önce önceki oyun sıfırlanıyor
            boyutla();//kaça kaç boyutta olacağını alıyor
            oyna();
            break;
        case 2:
            oynkayit();
            break;
        case 3://bu sadece kodu yazarken yardımcı olması için yaptığım durum
            sifirlama();
            break;
        default:
            printf("YANLIS DEGER\n");
            main();
    }
    return 0;
}
void oyna(){
    int a;
    FILE *oynn= fopen("oyun.txt","a");//içerisine komutları yerleştireceğiz
    if(oynn==NULL){
        printf("dosya açılma hatası");/*dosyanın açılmama durumu genel olarak tüm kod içerisinde
                                             dosya açılırsa bu işlem de yapılmalıdır ama bu kod özelinde
                                             her açtığım dosyayı bu şekilde göstermedim */
    }
    struct yonelim oyun;//yonelım adındaki structımızın büyüklüğünde oyun adlı bir değişken tanımlayıp yerleştirmeler yapılıyor
    printf("KOMUT ANLAMI \n1 Kalem aşağı \n2 Kalem yukarı \n3 Sağa dön \n4 Sola dön \n5 Yukarı dön \n6 Aşağı dön \n");//komutlar
    printf("komutlar şekildeki gibidir,sırasıyla kalem durumu yön ve adım sayısını giriniz\n");
    scanf("%d%d%d",&oyun.kalem,&oyun.yon,&oyun.adim);
    fprintf(oynn,"%d\t%d\t%d\n",oyun.kalem,oyun.yon,oyun.adim);//dosyanın içine yazılıyor
    printf("oyuna devam etmek için 1 oyunu çizdirmek için 0 a tıklayınız\n");//yönlendirme çizmek veya devam etmek
    scanf("%d",&a);
    if(a==1){
        fclose(oynn);
        oyna();//tekrardan aynı sorular sorulup dosyaya kayır ediliyor
    }
    else if(a==0){
        fclose(oynn);
        ciz_();//çizmek için fonksiyona yollanıyor
    }
    else {
        fclose(oynn);//dosya kapatma işlemi her fonksiyon sonunda yapılıyor tüm kodlarda yapılmazsa hata oluşabilir
        printf("yanlış değer girildi");
        main();
    }
}
void ciz_(){
    int k,l,m,n,x,y;/*m ve n dosyadan aldığımız cismin son konumunu belirtiyor k ve l nin işlevini ileride
                     daha iyi göreceğiz x ve y ise boyut dosyasından aldığımız satır sütun belirtiyor*/
    FILE *oynn= fopen("oyun.txt","r");
    FILE *kayitlar1=fopen("kayitler1.txt","r");
    FILE *kayitlar2=fopen("kayitler2.txt","r");
    FILE *oynn1=fopen("oyun1.txt","w");/*sadece bu dosyayı yazma durumunda açıyoruz çünkü bu eski oynanmış oyunu belirtiyor
                                                      yani oynn dosyasının içindeki kayıtlı komutların çizim halini oynn1 dosyasına kayıt edip
                                                      eğer önceki oyun görülmek istenirse o fonksiyon içerisinde açılıyor*/
    FILE *boyutla=fopen("boyutla.txt","r");
    if(oynn==NULL){
        printf("dosya açılma hatası");//sadece oynn dosyası için yapılmış ama hepsi için yapılması daha doğrudur sadelik açısından böyle bıraktım
    }
    struct yonelim oyun;/*yonelım adındaki structımızın büyüklüğünde oyun adlı bir değişken tanımlayıp yerleştirmeler yapılıyor
                        bu değişken oyna fonksiyonunda olanla aynı değildir sadece isim fazlalığını önlemek için yapıldı, örneğin
                        main de bir p değişkeni belirleyip sonra başka bir fonksiyonda yine p değişkeni belirlemek gibi ikisi de
                        yerel olduğu için birbirleriyle alakaları yoktur*/
    fseek(boyutla,0,SEEK_SET);/*fseek ile dosyayı her while girmeden başa konumlandırıyoruz çünkü dosya imleci dosyanın
                                                 sonuna işaret eder while bitince*/
    fscanf(boyutla,"%d\t%d",&x,&y);//satır sütun boyutlarını dosyadan alıyoruz
    char diz[x][y];//ve bu boyutlarla oluşturalacak dizi alanını belirliyoruz
    for(int i=0;i<=x-1;i++){
        for(int j=0;j<=y-1;j++){
            diz[i][j]='Y';/*burda dizinin tüm elemanlarına bir değer verme sebebim dizi açılıp
                          yazılırken ilk değersiz yerlere çöp değer atanmasıdır ben y olarak belirledim
                          isteyen istediği şekilde belirleyebilir*/
        }
    }
    fseek(oynn,0,SEEK_SET);//aynı şekilde genek olarak dosyaları başa konumlandırma işlemi
    while(!feof(oynn)) {
        fseek(kayitlar1, 0, SEEK_SET);
        fseek(kayitlar2, 0, SEEK_SET);
        fscanf(kayitlar1, "%d", &m);
        fscanf(kayitlar2, "%d", &n);
        fscanf(oynn, "%d\t%d\t%d\n", &oyun.kalem, &oyun.yon, &oyun.adim);
        printf("%d%d\n", m, n);//burada kodlama sırasında kontrol amaçlı boyutları görmek için yaptım
        switch (oyun.kalem) {/*aslında en başında aşağıda olan kod satırlarını hep if else ile yaptım fakat
                             fakat bu durum karışmaya çok müsait olduğunda ve case yapısını iç içe şekilde
                             kullanabildiğimizden switch case ile konumların hepsini baştan sona hangi anlama
                             geleceğini belirlemiş oluyoruz*/
            case 1:
                k = m, l = n;//bu eşitlemenin önemini aşağıda belirtiyorum
                switch (oyun.yon) {
                    case 3:
                        if(n==0){/*bunun yapılma amacını örnekle açıklayayım,örneğin 3 adım sağa gittik ve sonra
                                 aşağı yöne konumlanmak istedik burada 4. adımdaki sağdan başlanmaz 3. adımdaki sağdan
                                 başlanır ve aşağı gidilir ---
                                                             |şeklinde düşünebiliriz ve asıl burada yaptığımız n=0 ise
                                 n=1 yapmak şöyle oluyor örneklersek bir kişi 5 adım sağa atınca aslında dizi mantığında
                                 0,1,2,3,4 şeklinde dizinin 4. halinde durmuştur ve bende n=0 olarak başlaması gerekliliğinden
                                 "eğer 0 ise 1 yapalım çünkü 0 olunca -1 olarak başlar ve hatalar ortaya çıkar."dedim,*/
                            n=1;}
                        if (m + oyun.adim > x) {
                            while (m < x) {
                                diz[n-1][m] = '-';
                                m++;
                            }
                            m=x;
                            deger1(&m);/*deger1 fonksiyonunda dizide kalınan son yer w modunda bir dosyada tutuluyor
                                          ve adres gönrerek bunu bir dosyaya kayıt ediyoruz*/
                        }
                        else{
                            while (m < (k + oyun.adim)) {/*k=m ve l=n yapma sebebimiz burada oluşuyor eğer biz
                                                         normal m ve n kullanırsak her m artışında eşitliğin iki
                                                         tarafındaki değerler artacaktır ve sonsuz bir dönüye girecektir
                                                         m<m+oyun.adim şeklindeki eski halinden de anlayabiliriz*/
                                diz[n-1][m] = '-';
                                m++;
                            }
                            deger1(&m);}
                        break;
                    case 4:
                        if(n==0){
                            n=1;
                        }
                        if (m - oyun.adim <= 0) {
                            while (m -1>= 0) {
                                diz[n-1][m-1] = '-';
                                m--;
                            }
                            m=0;
                            deger1(&m);
                        }
                        else{
                            while (m-1 > k - oyun.adim) {
                                diz[n-1][m-1] = '-';
                                m--;
                            }
                            deger1(&m);}
                        break;
                    case 5:
                        if(m==0){
                            m=1;
                        }
                        if (n + oyun.adim > y) {
                            while (n < y) {
                                diz[n][m-1] = '|';
                                n++;}
                            n=y;
                            deger2(&n);}//m için yaptığımız durum
                        else{
                            while (n < (l + oyun.adim)) {//m için yaptığımız durum
                                diz[n][m-1] = '|';
                                n++;}
                            deger2(&n);
                        }
                        break;
                    case 6:
                        if(m==0){
                            m=1;
                        }
                        if (n - oyun.adim < 0) {
                            while (n >= 0) {
                                diz[n][m-1] = '|';
                                n--;
                            }
                            n=0;
                            deger2(&n);
                        }
                        else{
                            while (n-1 > (l - oyun.adim)) {
                                diz[n-1][m-1] = '|';
                                n--;
                            }
                            deger2(&n);
                        }
                        break;}
                break;
            case 2://kalem 2 modunda olursa boşluk ilerlemesi şeklinde oluyor ama geri kalan kısımlar yukarı ile aynıdır
                k = m, l = n;
                switch (oyun.yon) {
                    case 3:
                        if(n==0){
                            n=1;
                        }
                        if (m + oyun.adim > x) {
                            while (m < x) {
                                diz[n-1][m] = ' ';
                                m++;
                            }
                            m=x;
                            deger1(&m);}
                        else{
                            while (m < (k + oyun.adim)) {
                                diz[n-1][m] = ' ';
                                m++;
                            }
                            deger1(&m);}
                        break;
                    case 4:
                        if(n==0){
                            n=1;
                        }
                        if (m - oyun.adim < 0) {
                            while (m-1>= 0) {
                                diz[n-1][m-1] = ' ';
                                m--;
                            }
                            m=0;
                            deger1(&m);
                        }
                        else{
                            while (m-1 > k - oyun.adim) {
                                diz[n-1][m-1] = ' ';
                                m--;
                            }
                            deger1(&m);}
                        break;
                    case 5:
                        if(m==0){
                            m=1;
                        }
                        if (n + oyun.adim > y) {
                            while (n < y) {
                                diz[n][m-1] = ' ';
                                n++;}
                            n=y;
                            deger2(&n);}
                        else{
                            while (n < (l + oyun.adim)) {
                                diz[n][m-1] = ' ';
                                n++;
                            }
                            deger2(&n);}
                        break;
                    case 6:
                        if(m==0){
                            m=1;
                        }
                        if (n - oyun.adim < 0) {
                            while (n-1>= 0) {
                                diz[n-1][m-1] = '|';
                                n--;
                            }
                            n=0;
                            deger2(&n);
                        }
                        else{
                            while (n-1 > (l - oyun.adim)) {
                                diz[n-1][m-1] = ' ';
                                n--;
                            }
                            deger2(&n);
                        }
                        break;
                }
        }
    }
    if(m==0){
        m=1;
    }
    if(n==0){
        n=1;
    }//hiç ilerletilmemiş olma durumlarına karşın veya ilerletilip tekrar en başa dönme durumlarına karşın bir önlem
    diz[n-1][m-1]='*';/*dizilerde ilk elemanın 0 ile başlama durumunu ele alırsak örneğin 3 adım atan kişi 0,1,2 yani en son 2. bölümdedir
                      onun için bir eksiltme durumu uyguluyoruz*/
    for(int i=0;i<=x-1;i++){
        for(int j=0;j<=y-1;j++){
            printf("%c",diz[i][j]);//oluşan görünümü ekrana yazdırıyoruz
            fprintf(oynn1,"%c",diz[i][j]);//oluşann görünümü önceki oyun olarak düşünerek başka bir dosyanın içine yazdırıyoruz
        }
        fprintf(oynn1,"\n");
        printf("\n");
    }
    fclose(oynn);
    fclose(oynn1);
    fclose(kayitlar1);
    fclose(kayitlar2);
    fclose(boyutla);//tüm fonksiyonları kapatıp menüye yönlendiriyoruz
    printf("MENUYE YONLENDIRILIYORSUNUZ CIZIMI TEKRAR GORMEK ICIN MENUDEN 2-ESKI OYUN GORUNTULEYI SECINIZ\n\n\n");
    main();

}
void deger1(int *a){
    FILE *kayitlar1=fopen("kayitler1.txt","w");
    fprintf(kayitlar1,"%d",*a);
    fclose(kayitlar1);
}
void deger2(int *c){
    FILE *kayitlar2=fopen("kayitler2.txt","w");
    fprintf(kayitlar2,"%d",*c);
    fclose(kayitlar2);
}
void sifirlama(){/*dosya sıfırlama mantığı tüm dosyaları w modunda açınca imleç en başa gelir bizde bu durumu kullanıp
                 dosyaarımızı kapatıyoruz ama m ve n yani ilerleme komutlarımızı 0 olarak belirliyoruz eğer ciz_ fonksiyonu
                 içerisinde yaparsak da olabilir fakat düzen açısından daha doğru buldum*/
    FILE *kayitlar1=fopen("kayitler1.txt","w");
    FILE *kayitlar2=fopen("kayitler2.txt","w");
    FILE *oynn=fopen("oyun.txt","w");
    FILE *oynn1=fopen("oyun1.txt","w");
    FILE *boyutla=fopen("boyutla.txt","w");
    fprintf(kayitlar1,"0");
    fprintf(kayitlar2,"0");
    fprintf(oynn,"");
    fprintf(oynn1,"");
    fprintf(boyutla,"");
    fclose(kayitlar1);
    fclose(kayitlar2);
    fclose(oynn);
    fclose(boyutla);
}
void oynkayit(){
    int x,y;
    FILE *boyutla=fopen("boyutla.txt","r");
    fscanf(boyutla,"%d\t%d",&x,&y);//dosya boyutlarını bilme açısından yapmak zorundayız
    char diz[x][y];
    FILE *oynn1=fopen("oyun1.txt","r");
    fseek(oynn1,0,SEEK_SET);
    for(int i=0;i<=x-1;i++){
        for(int j=0;j<=y-1;j++){
            fscanf(oynn1,"%c",&diz[i][j]);
            printf("%c",diz[i][j]);/*eğer önceki oyunu görmek istersek burada kaydetmiş olduğumuz dosya açılır*/
        }
    }
    fclose(oynn1);
}
void boyutla(){
    FILE *boyutla=fopen("boyutla.txt","w");
    int x,y;//son olarak kişinin istediği boyutları isteyip dosyaya kaydetme fonksiyonu
    printf("OYUNU KACA KAC BIR YERDE OYNAMAK ISTERSINIZ(SATIR-SUTUN)?\n");
    scanf("%d%d",&x,&y);
    fprintf(boyutla,"%d\t%d",x,y);
    fclose(boyutla);
}
/* Bu kod C dilini tekrar edip biraz daha kavramamı sağlamlaştırmak için yazıldı, genel olarak bu kod özelinde çıkardığım sonuç
çok farklı ve bazen farkına varamadığımız hata ve problemler çıkabiliyor fakat üzerine yoğunlaşıp gerekirse en basit satırda oluşabilecek
hataları düşünerek, akıl yürüterek hem keyif alıp hem de kendimizi geliştiriyoruz,kodu inceleyen kişi eminim kendisine bir şeyler katacaktır.*/