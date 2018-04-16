void getHeader() {
  webpage = "<!DOCTYPE html>\n";
  webpage += "<html>\n";
  webpage += "<head>\n";
    webpage += "<meta charset=\"utf-8\"/>\n";
  webpage += "<meta http-equiv=\"refresh\" content=\"" + refreshPage + "\">\n";
  webpage += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">\n";
  webpage +="<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css\" integrity=\"sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp\" crossorigin=\"anonymous\">\n";
  webpage +="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js\"></script>\n";
  webpage +="<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>\n";
  webpage += javaScript;
  webpage += "<title>"+title+"</title>\n";
  webpage += "<style>\n";
  webpage += ".col-md-1{\n";
  webpage += "width:14%;\n";
  webpage += "font-size:14px;\n";
  webpage += "}\n";
  webpage += "</style>\n";
  webpage += "</head>\n";
    webpage += "<body style=\"background-color: black; height: -webkit-fill-available;\">\n";
      webpage += "<div class=\"container\">\n";
        webpage += "<div class=\"container-fluid\">\n";
        
          webpage +="<div class=\"centered\">\n";
                  webpage +="<h1 style=\"color:white\" class=\"text-center\">" + mainHeading + "</h1>\n";
                  webpage += "<h3 style=\"color:white\" class=\"text-center\">" + subHeading + "</h3>\n";
          webpage += "</div>\n";
          
          webpage += "<nav style=\"background-image: linear-gradient(to bottom,red 0,#222 100%);\" class=\"navbar navbar-inverse\">\n";
            webpage += "<div class=\"container-fluid\">\n";
                webpage += "<div class=\"navbar-header\">\n";
                  webpage += "<a class=\"navbar-brand\" href=\"#\">" + menuName + "</a>\n";
                webpage += "</div>\n";
              webpage += "<ul class=\"nav navbar-nav\">\n";
              webpage += "<li><a href=\"Product\">Product</a></li>\n";
              webpage += "<li><a href=\"Portfolio\">Portfolio</a></li>\n";
              webpage += "</ul>\n";
            webpage += "</div>\n";
          webpage += "</nav>\n";
          
}
