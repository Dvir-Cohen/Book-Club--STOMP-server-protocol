package bgu.spl.net.impl.stomp;

public class Frame {
    private  String type;
    private String StompCommand;
    private String genre;
    private String id;
    private String Username;
    private String Passcode;
    private String bookName;
    private String receiptId;
    private String bookStatus;

    public Frame(String msg){
        String[] arr = msg.split("\n");

        switch (arr[0]){
            case  "CONNECT": {
                this.Username = arr[3].substring(arr[3].indexOf(":")+1);
                this.Passcode = arr[4].substring(arr[4].indexOf(":")+1);
                type = "login";
                break;
            }
            case "SUBSCRIBE" :{
                this.genre = arr[1].substring(arr[1].indexOf(":")+1);
                this.id = arr[2].substring(arr[2].indexOf(":")+1);
                this.receiptId = arr[3].substring(arr[3].indexOf(":")+1);
                type = "join";
                break;
            }
            case "UNSUBSCRIBE":{
                this.genre = arr[1].substring(arr[1].indexOf(":")+1);
                this.id = arr[2].substring(arr[2].indexOf(":")+1);
                this.receiptId = arr[3].substring(arr[3].indexOf(":")+1);
                type="exit";
                break;
            }
            case "SEND": {
                this.genre = arr[1].substring(arr[1].indexOf(":") + 1);
                String[] arrWords = arr[2].split(" ");
                if (arrWords.length >2) {

                    if (arrWords[2].compareTo("added")==0 ) { // add book
                        this.Username = arrWords[0];
                        type = "add";
                        this.bookName = arrWords[5];
                    } else if (arrWords.length>3&&arrWords[3] .compareTo("borrow")==0) {
                        this.Username = arrWords[0];
                        type = "borrow";
                        this.bookName = arrWords[4];
                    } else if (arrWords[1].compareTo("has")==0 ) {
                        this.Username = arrWords[0];
                        this.bookName = arrWords[2];
                        type = "borrow1";
                    } else if (arrWords[0].compareTo("Taking")==0 ) {
                        this.Username = arrWords[3];
                        type = "borrow2";
                        this.bookName = arrWords[1];
                    } else if (arrWords[0].compareTo("Returning")==0) {
                        this.Username = arrWords[3];
                        type = "return";
                        this.bookName = arrWords[1];
                    }
                    } else if (arrWords.length>1&& arrWords[1].compareTo("status")==0 )
                        type = "status";
                else { // status back
                    bookStatus = arr[2];
                    type = "status1";
                }
                break;
            }
                case "DISCONNECT":{
                    type = "logout";
                    this.receiptId = arr[1].substring(arr[1].indexOf(":") + 1);
                    break;
                }

            }
        }

    public String getType (){return  type; }
    public String getUsername(){return Username; }
    public String getPasscode(){return Passcode; }
    public String getGenre(){return genre;}
    public String getBookName(){return bookName;}
    public int getReceiptId (){return Integer.parseInt(receiptId);}
    public int getId (){return  Integer.parseInt(id);}
    public String getBookStatus (){return bookStatus;}
}
