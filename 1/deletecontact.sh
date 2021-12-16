BOOK="address_book.txt"

echo -n "Enter the name of person whose contact to be deleted: "
read name

grep -iv $name $BOOK >> temp_address_book.txt
rm $BOOK
mv temp_address_book.txt $BOOK


echo "Contact of $name deleted successfully."	

exit 0
