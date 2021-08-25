BOOK="address_book.txt"

# ask user what to search
echo -n "Enter the name of person or contact of person to search for: "
read keyword

echo "Name : Phone Number"
grep -i $keyword $BOOK

exit 0