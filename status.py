import subprocess
import sys
import os
import shutil
import Image

def clean_extract():
	for entry in os.listdir("extract"):
		if not os.path.isdir(entry):
			subprocess.call(["rm", os.path.join("extract", entry)])

def htmlhead():
	return ("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">" +
		"<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\">\n" +
		"<head>\n<title>STATUS SkiOrDie</title>\n" +
		"<meta content=\"text/html; charset=utf-8\" http-equiv=\"Content-Type\" />" +
		css() + "</head>\n")

def css():
	return ("<style type=\"text/css\">\n" +
		"table { border-collapse: collapse; margin-top: 0;}" +
		"table th, table td { vertical-align: top; }" +
		"table td {border: 1px solid black;}" +
		"table th {border: 0;padding-top: 1em;text-align: left;}" +
		"table > thead > tr > th.status, table > tbody > tr > td.status {font-weight: bold;text-align: center;}"+
		"table > tbody > tr > td.ok {background-color: #6f6;}" +
		"table > tbody > tr > td.bad {background-color: #f66;}" +
        	"</style>")


def GenStatus(extracted):
	fout = open("status/index.html", "w")
	fout.write(htmlhead())
	fout.write("<body>\n<table>\n")
	for entry in extracted:
		fout.write("<thead><tr>\n")
      		fout.write("<th>%s</th><th></th><th class=\"status\">State</th>\n" % entry[0].rsplit('/', 1)[1])
    		fout.write("</tr></thead><tbody>\n")
		if len(entry[1]) > 0:
			for i in entry[1]:
				fout.write("<tr>\n")
    				fout.write("<td><a name=\"%s\"></a>%s</td><td><small><IMG BORDER=\"0\" SRC=\"%s\"></small></td><td class=\"status ok\"></td>\n" % (i.rsplit('/', 1)[1], i.rsplit('/', 1)[1], i))
				fout.write("</tr>\n")
		else:
			fout.write("<tr><td><a name=\"???\"></a>???</td><td><small></small></td><td class=\"status bad\"></td>\n</tr>\n")
		fout.write("</tbody>\n")
	fout.write("</table>\n</body>\n</html>")
	fout.close()

def launch_extract(entry):
	entry_extracted = []
	name_entry = entry.rsplit('/', 1)[1]
	DEVNULL = open(os.devnull, 'wb')
	process = subprocess.Popen(["./skiordietoolz", "-x", entry], stdout=DEVNULL, stderr=DEVNULL)
        process.wait()
	DEVNULL.close()
	if process.returncode == 0:
		if os.access(os.path.join("status", name_entry), os.R_OK):
			shutil.rmtree(os.path.join("status", name_entry))
		os.mkdir(os.path.join("status", name_entry))
		num = 0
		for res in os.listdir("extract"):
			if not os.path.isdir(os.path.join("extract", res)):
				try:
					img = Image.open(os.path.join("extract", res))
					new_file_name = name_entry + "_" + str(num) + ".bmp"
					shutil.copy(os.path.join("extract", res), os.path.join("status", name_entry, new_file_name))
					entry_extracted.append(os.path.join(name_entry, new_file_name))
					num += 1
				except(IOError):
					print "[-] Error " + os.path.join("extract", res)
					clean_extract()
					return [entry, []]
	clean_extract()
	return [entry, entry_extracted]


def main():
	extracted = []
	if len(sys.argv) != 2:
		print "[-] Need path to SkiOrDie"
		sys.exit(1)
	for entry in os.listdir(sys.argv[1]):
		if not os.path.isdir(entry):
			extracted.append(launch_extract(os.path.join(sys.argv[1], entry)))
	GenStatus(extracted)

if __name__ == "__main__":
    main()
