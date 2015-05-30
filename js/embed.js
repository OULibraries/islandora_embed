/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

(function ($) {
    
    /**
   * Modify the display of embedded islandora bookreader.
   */
    Drupal.behaviors.embedBookReader = {
        attach: function(context, settings) {
      
            var shareLink = $(".BRicon.share.cboxElement");
            if(shareLink) {
                shareLink.remove();
            }
        
            var spanBRreturn = $("span#BRreturn");
            if(spanBRreturn) {
                spanBRreturn.remove();
            }
        
            // make the title font size smaller:
            var bookTitle = $("h1#page-title");
            if(bookTitle) {
                bookTitle.css("font-size", "16px");
            }
        
            var bookSearchForm = $("#textSrch");
            if(bookSearchForm) {
                bookSearchForm.remove();
            }
        
            var bookBRnavpos = $("div#BRnavpos");
            if(bookBRnavpos) {
                bookBRnavpos.remove();
            }
        
            // when display the book reader in the two page view mode, the BRtwopageview div top is set wrong:
            var bookBRtwopageview = $("div#BRtwopageview");
            if(bookBRtwopageview) {
                bookBRtwopageview.css("top", "35px");
            }
        
            // adjust the height of the book reader based on the iframe height:
            var height = Drupal.settings.islandora_bookreader_embed.height;
            var bookBRcontainer = $("div#BRcontainer");
            if(bookBRcontainer) {
                bookBRcontainer.css("height", parseInt(height)-112);
            }

            // hide the side bars to better fit the book viewer in the iframe:
//            var body = $("body");
//            if(body.hasClass("one-sidebar")){
//                body.removeClass("one-sidebar");
//            }
//            if(body.hasClass("sidebar-first")){
//                body.removeClass("sidebar-first");
//            }
//            if(!body.hasClass("no-sidebars")){
//                body.addClass("no-sidebars");
//            }
                
        }
    }
})(jQuery);