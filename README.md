MD5AWSUM
==================

MDAwSum is a one-stop tool for calculating md5checksums, verifying the integrity of downloaded files, and maintaining a reverse-lookup hashtabe of md5 hashes.

Usage
------------------
```
MD5AwSum [options] <input>   
Options:    
	-h, --help		show this information   
	-l, --lookup		lookup the given hash   
	-a, --add		add the given url to the local table
	-r, --remove		remove the given url from the local table
	-s, --sources		show repositories that are locally stored
	-d, --download		download the given url and lookup
	-u, --update		update the local table, updates
				all urls if it is not specified
	-aff, --add-from-file	reads a file where each line is a url
				each url is added to the table
	-e, --entry		will read the file, hash and add to local
				repo or will take the given name and
				hash and add it to the local repo
	-g, --generate		given a directory will hash and store
				all files in that directory, defaults
				to current directory if not given.
```
