# FILE HANDLING
- File (du duoc xay dung bang cach nao): la day cac unsigned char (0-255)
- Khi doc den cuoi File ta duoc ma ket thuc File EOF (-1)
- Moi File co 1 con tro chi vi

---
### #include <stdio.h>
- Nhom ham cap 1: thuc hien doc ghi nhu DOS -> kho su dung, toc do nhanh hon
- Nhom ham cap 2: duoc xay dung tu cac ham cap 1 -> de su dung
	- co dich vu truy xuat cho tung kieu du lieu
	- C cung cap 1 Buffer (mac dinh 512 bytes), moi lan doc ghi se tien hanh tren Buffer
		- khi ghi, data duoc day vao Buffer, khi nao Buffer day moi day len File
		- khi doc, data duoc lay tu Buffer, khi Buffer trong may moi lay data tu File
	- lam viec thong qua bien con tro FILE

---
### BINARY - Kieu nhi phan
- Bao toan du lieu: data ghi tren File theo cac byte nhi phan nhu tren Memory
- Ma ket thuc File: EOF va ham feof() cho gia tri != 0
### TEXT - Kieu van ban
- Ma chuyen dong: LF (ma 10) -> CR (ma 13) LF (ma 10) (cho phu hop vs DOS)
- Ma ket thuc File: SUB (ma 26), EOF va ham feof(fp) != 0 (= 1)

---
## BINARY - TEXT
### OPEN - CLOSE - CLEAN BUFFER - ERROR
#### fopen
	FILE *fopen(const char *file_name, const char *type);
	@return: FILE* fp | NULL
| type | Description |
| ----------- | ----------- |
| "r" "rt" | read mode TEXT, loi neu file ko ton tai |
| "w" "wt" | write mode TEXT, tao file moi, xoa file neu da ton tai |
| "a" "at" | write mode TEXT, ghi bo sung, tao moi file neu chua ton tai |
| "rb" | read mode BINARY, loi neu file ko ton tai |
| "wb" | write mode BINARY, tao file moi, xoa file neu da ton tai |
| "ab" | write mode BINARY, ghi bo sung, tao moi file neu chua ton tai |
| "r+" "r+t" | read/write mode TEXT, loi neu file ko ton tai |
| "w+" "w+t" | read/write mode TEXT, tao file moi, xoa file neu da ton tai |
| "a+" "a+t" | read/write mode TEXT, ghi bo sung, tao moi file neu chua ton tai |
| "r+b" | read/write mode BINARY, loi neu file ko ton tai |
| "w+b" | read/write mode BINARY, tao file moi, xoa file neu da ton tai |
| "a+b" | read/write mode BINARY, ghi bo sung, tao moi file neu chua ton tai |
#### fclose
	int fclose(FILE *fp);
	@return: 0 | EOF
quy trinh: day data con trong Buffer len File khi ghi, xoa Buffer khi doc
#### fcloseall
	int fcloseall(void);
	@return: so File duoc dong | EOF
#### fflush
	int fflush(FILE *fp);
	@return: 0 | EOF
clean Buffer cua File
#### fflushall
	int fflushall(void);
	@return: so FILE dang mo | EOF
clean Buffer cua all File
#### ferror
	int ferror(FILE *fp);
	@return: 0 | != 0
kiem tra loi thao tac tren File
#### perror
	void perror(const char *s);
thong bao loi he thong
#### feof
	int feof(FILE *fp);
	@return: != 0 if get EOF | 0
kiem tra EOF, can than khi dung, gia tri phu thuoc vao ham get truoc do
#### unlink - remove
	int unlink(const char *file_name);
	@return: 0 | EOF
	void remove(const char *file_name);
xoa File
### FILE POSITION LOCATOR
#### rewind
	void rewind(FILE *fp);
chuyen con tro ve vi tri dau File
#### fseek
	int fseek(FILE *fp, long sb, int posit);
	@param:	sb: so byte can di chuyen
			posit: vi tri xuat phat
			posit = SEEK_SET | SEEK_CUR | SEEK_END
	@return: 0 | != 0
di chuyen con tro chi vi den vi tri mong muon
NOTE: ko nen dung tren kieu TEXT
#### ftell
	long ftell(FILE *fp);
	@return: int | -1L
vi tri hien tai cua con tro chi vi so voi dau File (byte dau danh so 0)
### PUT - GET CHARACTER
#### putc - fputc
	int putc(int ch, FILE *fp);
	int fputc(int ch, FILE *fp);
	@return: ch | EOF
#### getc - fgetc
	int getc(FILE *fp);
	int fgetc(FILE *fp);
	@return: int | EOF

---
### TEXT
#### fprintf
	int fprintf(FILE *fp, const char* ctrlstring, ...);
	@return: int so byte ghi | EOF
ghi data theo khuon dang
#### fscanf
	int fscanf(FILE *fp, const char* ctrlstring, ...);
	@return: int so truong dc doc
doc data theo khuon dang
#### fputs
	int fputs(const char *s, FILE *fp);
	@return: ky tu cuoi ('\0' ko ghi len file) | EOF
ghi string
#### fgets
	char *fgets(char *s, int n, FILE *fp);
	@return: s | NULL (error hoac EOF)
doc string

---
### BINARY
#### putw
	int putw(int integer, FILE *fp);
	@return: integer | EOF
ghi 1 so nguyen duoi dang 4 byte len File
#### getw
	int getw(FILE *fp);
	@return: integer | EOF
doc 1 so nguyen (4 byte) tu File
#### fwrite
	int fwrite(void *ptr, int size, int n, FILE *fp);
	@param:	ptr: con tro tro toi vung nho chua du lieu can ghi
			size: kich thuoc cua mau tin theo byte
			n: so mau tin can ghi
	@return: int so mau in thuc su ghi dc ( <= n)
ghi n mau tin kich thuoc size tu ptr len File
#### fread
	int fread(void *ptr, int size, int n, FILE *fp);
	@param:	ptr: con tro tro toi vung nho chua du lieu doc duoc
			size: kich thuoc cua mau tin theo byte
			n: so mau tin can doc
	@return: int so mau tin thuc su doc dc ( <= n)
doc n mau tin kich thuoc size tu File chua vao vung nho ptr tro toi
fread() va fwrite() thuong dung de doc ghi cac doi tuong co cung do lon nhu struct, integer, float,...

---
### STREAMS AND THREADS
#### flockfile
	void flockfile(FILE *stream);
#### ftrylockfile
	int ftrylockfile(FILE *stream);
	@return: 0 | != 0
#### funlockfile
	void funlockfile(FILE *stream);

---
![Streams and Threads](https://live.staticflickr.com/65535/52983834560_8a922a247d_b.jpg)

---
![File handling](https://live.staticflickr.com/65535/52983605914_5ccfb8f8e0_b.jpg)
