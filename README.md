# islandora_embed
An islandora module that is used to provide oEmbed services

Steps to set up oembed services provider:

1. Install and enable modules:
    Link(to use oembed field module); oembed; themekey;

2. Install and enable the entity iframe theme;

3. Go to themekey configure, select “user interface”, and select “theme switching rule chain”, and then set up new rules on drupal:path (islandora/object/%) and system:query_param (ui=embed);

4. Install the islandora_embed module. This module handles the oembed requests and can also respond with pure JSON objects so it can provide API services;

5. if the domain name has significance for its first part, i.e. 192.168.11.142, the code of the oembed core module should be modified:
    for the function of _oembedcore_get_host($uri){
     *************
    }
    Note: this should be a bug with this module
    other regular websites like www.youtube.com, the first part of ‘www’ has no much meaning for its API so the current function works, but we have to be careful about this when implementing our oembed services.

6. Set up the oembed module by adding new providers.

7. For adding oembed field to a content type, create new field of "Link", and then click “manage display settings”, set the oembed field display to be "Oembed". 
    For islandora internet book reader, set the width == height will make the embedded frame pretty.

8. To make our oembed url work with drupal user comments:
    8.1 Enable the oembed filter module and create an oembed filter, and let it to be the 
                  default filter;
    8.2 Make the url to be like the following format:
        http://192.168.11.142:8181/islandora/embed/object/islandora%253A18?height=500&width=500 
          (the width and height are optional: the system can provide default dimension parameters)

/** unnecessary now **/        
9. Code changes to the islandora_internet_archive_bookreader module:
    9.1 New javascript file for adjusting the appearance of the book reader:
         embed_bookreader.js
    9.2 The islandora_internet_archive_bookreader module: theme/theme.inc is also 
                    modified for accommodation of the oembed services.
**/
     
    
     
     
Examples about how to use:

Set up a new oembed service provider:
1. Install and enables the modules of “Link”, “oembed”.

2. Go to “modules”-> “oembed Core” -> “config” -> “Providers”, click “add”.

3. Type in “Name” and “Title”.

4. For “Endpoint”, it is domain+”islandora/embed/”.  For example: http://192.168.11.142:8181/islandora/embed/

5. For “Schemes”, now we have domain+”/islandora/embed/object/*”. For example:
    http://192.168.11.142:8181/islandora/embed/object/*
    Note: we can add more schemes in the future if needed.

6. Save.

Create an oembed field for a content type:
1. Go to structure, modify or add a content type, click “manage fields”, add a new field with type “Link”.

2. Check “Absolute URL” and “Validate URL” under “Browse available tokens”.
    Link Title: select “No Title”.
    Link Target: “Default”.
    Number of values: select “Unlimited”.

3. Save.

4. Go to add new content type and select the content type containing the oembed field.

5. For oembed field, type the url for EMBED-LINK. i.e., 
    http://192.168.11.142:8181/islandora/embed/object/islandora%3A18

6. save. 

7. Go to the node page and then the embedded stuff will be there!

Embedding islandora object contents within user comments and other editors:
1. Make sure “oembed Filter” has been installed and enabled.
2. Go to “modules” -> “Filter” -> “Add text format”.
3. Give a name and set up the roles.
4. Check “oembed legacy filter” and “oembed filter”.
5. Optionally, set up the maximum width, height, and/or requets options for the embed filter.
6. Save.
7. Move the new created oembed filter to top of the filter list so it becomes the default oembed filter.
8. Save changes.
9. The format of the urls fed to oembed is like this:
    http://192.168.11.142:8181/islandora/embed/object/islandora%253A51?height=300&width=300, where the height and weight are optional.
10.Now when the users make comments. If they type the urls, the islandora objects will show up.

