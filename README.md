///Issuse Faced While Building the AOSP//////




All HALs in device manifest are declared in FCM <= level 202404
ERROR: files are incompatible: android.hardware.carsenze@18446744073709551615.1::ICarsenze/default is deprecated in compatibility matrix at FCM Version 202404; it should not be served.
    because it matches android.hardware.carsenze.ICarsenze/default (@1) from /system/etc/vintf/compatibility_matrix.8.xml: Success
INCOMPATIBLE



-->
Added following things into compatibility_matrix.20404.

 <hal format="aidl" optional="true">
        <name>android.hardware.carsenze</name>
        <version>1</version>
        <interface>
            <name>ICarsenze</name>
            <instance>default</instance>
        </interface>
    </hal>
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-->
the HAL service does not able to open the file.


07-03 11:56:36.622  3375  3375 D Carsenze_System_APP: **-Requesting for CPU Information-**
07-03 11:56:36.622   528   528 D Carsenze_HAL_service: ***-CPU Info is REQUESTED-***
07-03 11:56:36.617   528   528 W android.hardwar: type=1400 audit(0.0:168): avc:  denied  { open } for  path="/proc/stat" dev="proc" ino=4026532030 scontext=u:r:hal_carsenze_service:s0 tcontext=u:object_r:proc_stat:s0 tclass=file permissive=0
07-03 11:56:36.617   528   528 W android.hardwar: type=1300 audit(0.0:168): arch=c000003e syscall=257 success=no exit=-13 a0=ffffff9c a1=5e9948499eb4 a2=80000 a3=0 items=0 ppid=1 auid=4294967295 uid=1000 gid=1000 euid=1000 suid=1000 fsuid=1000 egid=1000 sgid=1000 fsgid=1000 tty=(none) ses=4294967295 exe="/vendor/bin/hw/android.hardware.carsenze-service" subj=u:r:hal_carsenze_service:s0 key=(null)
07-03 11:56:36.622   528   528 E Carsenze_HAL_service: **-Failed to open /proc/stat-**   

solution:
---------

added the following permissions into system/sepolicy/vendor/hal_carsenze_service.te
.......
allow hal_carsenze_service proc_stat:file open;
allow hal_carsenze_service proc_stat:file read;
.......

we can know the missing sepolicies by running this commands.
1)adb pull /sys/fs/selinux/policy
2)adb logcat -b events -d | audit2allow -p policy


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-->added the following policies into system/sepolicy/vendor/hal_carsenze_service.te to allow the service to open the /sys/class/net files

allow hal_carsenze_service sysfs_net:dir search;
allow hal_carsenze_service sysfs_net:file read;
allow hal_carsenze_service sysfs_net:file open;
