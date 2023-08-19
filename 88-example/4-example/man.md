# FAT implementation

![Volume structure](https://live.staticflickr.com/65535/52997031616_dbcf424ac9_b.jpg)

## Reserved Region

### Boot Sector and BIOS Parameter Block

NOTE: This document does not describe all variables contained in the FAT file system driver implementation. There are variables to validate interoperability and correctness of the resultant FAT implementation.

| Name | Unit | Type | Description |
| ----------- | ----------- | ----------- | ----------- |
| BPB_BytsPerSec | Byte | Size | Bytes per sector (512, 1024, 2048 or 4096) |
| BPB_SecPerClus | Sector | Size | Sectors per cluster (1, 2, 4,..., 64, 128) |
| BPB_RsvdSecCnt | Sector | Size | Number of sectors in the reserved region |
| BPB_NumFATs | FAT | - | The count of FATs (2 is recommended) |
| BPB_RootEntCnt | 32-byte entry | - | FAT12-FAT16: Count of 32-byte entries in the root directory. FAT32: 0 |
| BPB_TotSec16 | Sector | Size | FAT12-FAT16: Count of sectors on the volume, if be 0 refer to BPB_TotSec32. FAT32: 0 |
| BPB_FATSz16 | Sector | Size | FAT12-FAT16: Count of sectors occupied by one FAT. FAT32: 0, refer to BPB_FATSz32 |
| BPB_TotSec32 | Sector | Size | Count of sectors on the volume. FAT12-FAT16: contains the sector count if BPB_TotSec16 is 0 |
|||||
| BPB_FATSz32 | Sector | Size | FAT32: Count of sectors occupied by one FAT. BPB_FATSz16 must be 0 |
| BPB_RootClus | - | - | The cluster number of the first cluster (should be 2) |

Incomplete...

## Man program
use commands like command line linux

pwd                 Print working directory path
ls                  List files and folders in working directory
cd [folderName]     Change directory to the folder folderName
cd [..]             Change directory to the parent folder
cd [~]              Change directory to the Root directory
cat [fileName]      Print file fileName
exit                Exit program
