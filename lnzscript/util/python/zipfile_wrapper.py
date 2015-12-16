'''
File.zipExtract(strZipfile, strDirectory) // returns # of extracted files or false on error
File.zipList() //returns entries
File.zipList(true) //returns only files, not folders
File.zipCreate(strDirectory)
'''


import os
import zipfile

from cStringIO import StringIO


def zipfile_list( filename, includeFolders=False):
    try:
        zf = zipfile.ZipFile( filename )
    except IOError: return False
    except zipfile.BadZipFile: return False
    except: return False
    
    namelist = zf.namelist()
    if not includeFolders: namelist = filter( lambda x: not x.endswith( '/' ), namelist )
    return namelist

#http://aspn.activestate.com/ASPN/Cookbook/Python/Recipe/465649
def zipfile_extract( filename, dir ):
    try:
        zf = zipfile.ZipFile( filename )
    except IOError: return False
    except zipfile.BadZipFile: return False
    except: return False
    namelist = zf.namelist()
    dirlist = filter( lambda x: x.endswith( '/' ), namelist )
    filelist = filter( lambda x: not x.endswith( '/' ), namelist )
    # make base
    pushd = os.getcwd()
    if not os.path.isdir( dir ):
        os.mkdir( dir )
    os.chdir( dir )
    
    # create directory structure
    dirlist.sort()
    for dirs in dirlist:
        dirs = dirs.split( '/' )
        prefix = ''
        for dir in dirs:
            dirname = os.path.join( prefix, dir )
            if dir and not os.path.isdir( dirname ):
                os.mkdir( dirname )
            prefix = dirname
    # extract files
    err = False
    count = 0
    try:
        for filename in filelist:
            out = open( filename, 'wb' )
            buffer = StringIO( zf.read( filename ))
            buflen = 2 ** 20
            datum = buffer.read( buflen )
            while datum:
                out.write( datum )
                datum = buffer.read( buflen )
            out.close()
            count+=1
    except:
        err = True
    finally:
        os.chdir( pushd )
    if err: return False
    else: return count


def zipfile_create(strDirectory, strFilename):
    try:
        zf = zipfile.ZipFile( filename, 'w',  zipfile.ZIP_DEFLATED)
    except: return False
    
    err = False
    pushd = os.getcwd()
    
    os.chdir(strDirectory)
    # add contents to the archive.
    try:
        for dirpath, dirnames, filenames in os.walk(strDirectory):
            for filename in filenames:
                print dirpath + '/' + filename
        
    except:
        err = True
    finally:
        os.chdir( pushd )
    return not err

if __name__=='__main__':
    testf = r'C:\Documents and Settings\bfisher\My Documents\winrhythm.zip'
    #~ testf = r'C:\Documents and Settings\bfisher\My Documents\web hosting.txt'
    z = zipfile.ZipFile(testf, 'r')
    print z.namelist()
    
    strDirectory = r'C:\Documents and Settings\bfisher\My Documents\lnzbinary'
    os.chdir(strDirectory)
    for dirpath, dirnames, filenames in os.walk(strDirectory):
        for filename in filenames:
            if dirpath.startswith(strDirectory):
                dirpath
            print dirpath + '/' + filename
    
    #~ z = zipfile.ZipFile('test.zip','w', zipfile.ZIP_DEFLATED)
    #~ z.write('test.txt')
    #~ z.close()