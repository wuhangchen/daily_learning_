## Solid compression(固实压缩)

this artical mainly from wikipedia ,and i summury some key knowledge point .
#### what is solid compression
    solid compression is a method for data compression of multiple file,wherein all the uncompressed files are concatenated  and treated as a single data block,such an archive is called a solid archive,it is used natively in the 7z and rar formats ,as well as indirectly in tar-based formats such as .tar.gz and .tar.bz2..
    on the country ,the zip format is not solid because it stores separately compressed files,though solid compression can be emulated for small archives by combining the files into an uncompressed archive file and then compressing that archive file inside a second compressed zip file.

#### better understanding
compressed file formats often feature both compression and archiving ,one can combine these in two natural waay.

-compress the individual files,and then archive into a single file;
-archive into a single data block,and then compress.

in unix,compression and archiving are traditionally separaate operations ,which allow one to understand this distinction.

-compressing individual ifles and then archiving would be a tar of gzip 'ed files -this is very uncommon,while..
-archiving via tar and then compressing yields a compressed archive:a .tar.gz-and this is solid compression.


#### benefits
solid compression allows for much better compression rates when all the files are similar,which is often the case if they are of the same file format,it can also be efficient when archiving a large number of small files.
#### costs
there are also have some extra costs.

-for example,getting a single file out of a solid archive orginally required processing all the files beforei it,so modifying solid archives could be slow and inconvenient ,later version of 7z use a variable solid block size,so that only a limited amount of data must be processed in order to extract on file.
-if the archive becomes even slightly damaged ,some of the data after the damaged part can be unusable,whereas in a non-solid archive format,usually only one file is unusable and the sbsequent ifles can usually  still be extracted .
