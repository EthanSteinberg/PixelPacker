for i in $*
do
cat licenseHeader | cat - $i > aTemp
mv aTemp $i
done
