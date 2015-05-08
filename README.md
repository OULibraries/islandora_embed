# oEmbed Provider for Islandora

## Note: this module is an early-stage work-in-progress.


## Introduction
An Islandora module that enables Islandora Objects to be embedded via oEmbed. Currently works with the Islandora Book Solution Pack. 


## Requirements

This module requires the following modules/libraries:
* oEmbed Core and oEmbed Provider from https://www.drupal.org/project/oembed

You're likely to want to be able to specify an appropriate display for oEmbeded content. There are a number of ways to do this, but we'll assume here that you're using:

* [ThemeKey](https://www.drupal.org/project/themekey) 
* [Entity iframe theme](https://www.drupal.org/project/entity_iframe_theme). 


## Configuration


### Islandora as an oEmbed provider:

1. Install and enable: oembed_core, oembed_provider, themekey, entity_iframe_theme, and islandora_embed
1. Configure a ThemeKey Switching Rule Chain for `drupal:path` = `islandora/object/%` and `system:query_param` = `ui=embed` to switch to the Entity Iframe theme. 

### Configure Drupal to use your Islandora oEmbed provider


    
Set up a new oembed service provider:

1. Install and enable: link, oembed_field, and oembed
1. Add a new provider in the oEmbed Configuration menu with Endpoint: `$host-url/islandora/embed/` and Schemes: `$host-url/islandora/embed/object/*`

Now you can add an oEmbed field to a content type or add the oEmbed fitler to a text format. See the oEmbed module documentation for details. 

