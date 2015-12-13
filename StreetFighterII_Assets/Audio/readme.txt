RENSET v0.6  (Rename RSN Sets)
Created: October 24, 2006 by Tafoid (tafoid@yahoo.com)
Last Updated: December 4, 2009


SYSTEM Requirements
-------------------
Windows 2000 or Windows XP (I have not tried with Windows 95/98, but I'd
have to assume it would work all the same)


What is it?
-----------
If you are like me, while you value ALL the work put into the 
compilation/creation/maintaining of the SNESMusic.org's RSN sets, you soon
notice the filenames are not as descriptive most people would probably like
them to be.

At first, I came up with a DAT file for use with CLRMAME which would scan
your RSN sets and rename when an official set was found.  This worked pretty
well, but it had an annoying drawback that required either each RSN needing
to be in it's own folder or all RSN sets needed to be in one large ZIP file
before CLRMAME would even care to touch it.  Thus, RENSET was born..

This small application was created allow you to keep your RSN files
uncompressed and through the CLRMAME DAT file I created, will rename your
RSN's without the need of playing by CLRMAME's rules!!


Files included in this archive
------------------------------
renset.exe  - Main Program which does the dirty work
readme.txt  - You are reading this!  :)

Files not included, but required
--------------------------------
rsnsets.dat - CLRMAME DAT file for the RSN files from SNESMusic.org
	      This is not included in the archive, but REQUIRED!!!
              You can find this at http://SNESMusic.org/v2/players.php


How To Use
----------
Extract and place ALL files from this downloaded archive into your folder which
contain your .RSN files.  Then, simply execute "RENSET.EXE".  The program will
ignore all files NOT having an RSN extention and will only rename those which
have matches in the current CLRMAME DAT file.  This program should not delete
any files which are not already duplicated.  If you feel at all wary, please be
sure to back up your .RSN files before the renaming process.

It really cannot get much more simple to use than that... Can it?


What's New with this release
----------------------------
v0.6    December 4, 2009

- Added a catch for possible invalid .RSN files (with filesize under 20 bytes).
  This should fix any application crashes people have had with attempting to
  determine CRC's on such files.  If any problemed files are found, they are
  displayed after all the other CRC's are determined.


v0.5	August 6, 2009

- Implemented an internal CRC32 check eliminating the need of the external
  REHASH.exe program.  You shouldn't notice too much of a slowdown, if any
  at all!

- More code cleanups and format changes to screen output.

    
v0.3	February 24, 2007

- Fixed a problem due to REHASH's inability to recognize "%" in filenames.
  This effected the set "Marchen Adventure Cotton 100% [cttn]".  While my
  program internally saw the filenames the same, when I read the CRC32 of it,
  and extracted it's found filename to compare - the output from REHASH did
  not report the %, causing my program to trying to delete and rename using
  the invalid filename.  If future filenames with "%" show up, I will need
  need to work out a better solution.

- Internal cleanups of code.


v0.2	October 26, 2006

- Included a bit of error checking.  Problems arose when I tried to rename a
  file to a name which already existed - as well as problems with file with
  names which simply were case-changed (eg. Aryol/aryol).  Not too useful when
  you have updated sets and this program fails to rename them.

- In the same respect, file checking at beginning was added to make sure you
  have, in folder, all the required helper programs before Renset executes.

- Added dialog to mention how many sets you are missing or if your collection
  is complete (based on the DAT information).  If you have missing files, you
  need to check the "rsnmiss.txt" file for a list of files that were not found
  in folder.  This old "rsnmiss.txt" file will be deleted if you collection is
  completed.

V0.1	October 24, 2006

- Initial Release


Credits/Thanks
--------------
Datschge of SNESMusic.org - For his need for such a program which compelled
me to bare down and create this application.  I also wish to thank all the
contributers to this .RSN archive.  Your sacrifices do not go unnoticed!!!!


Software References
-------------------
CLRMAME - http://www.clrmame.com 
This program is a very handy file management utility.  With the help of DATA
files, you can keep your files properly updated.


CONDITIONS OF USE/DISCLAIMER:
-----------------------------
This product is FREEWARE.  I will accept NO RESPONSIBILITY (directly or
indirectly) to any damage (temporary or permanent) that this program or any
associated programs may do.  Also, I ask that you keep this archive together
and do not add or delete anything to/from the ZIP file.  You may also NOT
modify, add or delete (HACK) into Renset, as it is protected by copyright.
Please ask for permission if you plan to make this file available ANYWHERE
other SNESMusic.org.  I do not want this program to be included in any PAK,
CD, or ANY other compilation without my obtained permission.  Not responsible
for any typographical or spelling errors ;)
