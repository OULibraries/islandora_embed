<?php

/**
 * This class provides the function to output object-related information.
 */

@include_once 'sites/all/libraries/tuque/Object.php';

Class FedoraObjectExtended extends FedoraObject
{
    public function __construct($id, $repository)
    {
        parent::__construct($id, $repository);
    }
    
    /**
     * Expose the content model information.
     * 
     * return string
     * content model name
     * e.g. "islandora:bookCModel" for islandora bookreader type (good for version 7.x-1.4 or older); 
     * Note: In the head verion, however, things have changed:
     *      1) The model information is like "info:fedora/islandora:bookCModel";
     *      2) The model information is NOT put at the first position of the array that carries the object model information;
     */
    public function getFedoraObjectModel()
    {
        try {
            $profile = $this->getFedoraObjectProfile();
            foreach($profile['objModels'] as $modelInfo) {
                if(strpos($modelInfo, "islandora:") !== false) {
                    $model_arr = explode(':', $modelInfo);
                    $size = count($model_arr);//"info:fedora/islandora:bookCModel"
                    return $model_arr[$size-1];
                }
            }
            throw new Exception("The islandora object model information is NOT retrieved!", null, null);
        } catch (Exception $exc) {
            echo $exc->getTraceAsString();
        }
    }

    /**
     * Expose the profile of fedora object.
     * 
     * @return array
     * fedora object profile contains a general description of this object.
     */
    public function getFedoraObjectProfile() 
    {
        return $this->objectProfile;
    }

}

/**
 * This class generates appropriate responses based on different request types.
 */
Class RespsonseGenerator
{
    protected $fedoraObjExt;
    protected $iframeHeight;
    protected $iframeWidth;
    protected $height;
    protected $width;


    /**
     * constructor
     * 
     * @param FedoraObjectExtended $fedoraObjExt
     * @param string               $base_url
     * @param int                  $height
     * @param int                  $width
     * @param int                  $iframeHeight
     * @param int                  $iframeWidth
     */
    public function __construct(FedoraObjectExtended $fedoraObjExt, $base_url, $height = 500, $width = 500, $iframeHeight = 500, $iframeWidth = 500)
    {
        
        if($height != 500) {
            $iframeHeight = $height; 
        }
        if($width != 500) {
            $iframeWidth = $width; 
        }
        
        $this->fedoraObjExt = $fedoraObjExt;
        $this->height = $height;
        $this->width = $width;
        $this->iframeHeight = $iframeHeight;
        $this->iframeWidth = $iframeWidth;
        $this->base_url = $base_url;
    }
    
    /**
     * set iframeHeight
     * 
     * @param int $iframeHeight
     */
    public function setIframeHeight($iframeHeight)
    {
        $this->iframeHeight = $iframeHeight;
    }
    
    /**
     * set iframeWidth
     * 
     * @param type $iframeWidth
     */
    public function setIframeWidth($iframeWidth)
    {
        $this->iframeWidth = $iframeWidth;
    }
    
    /**
     * set height
     * 
     * @param int $height
     */
    public function setHeight($height)
    {
        $this->height = $height;
    }
    
    /**
     * set width
     * 
     * @param int $width
     */
    public function setWidth($width)
    {
        $this->width = $width;
    }
    
    /**
     * Generate the JSON object for Oembed requests
     */
    public function getJSONResponse()
    {
        
        $resArray = Array();
        $resArray['height'] = $this->height;
        $resArray['width'] = $this->width;
        $resArray['provider_name'] = 'Galileo World';
        $resArray['provider_name'] = urlencode($this->base_url);
        //$resArray['title'] = $this->fedoraObjExt->label;
        
        $fedoraObjExt = $this->fedoraObjExt;
        $objModel = $fedoraObjExt->getFedoraObjectModel();        
        switch($objModel){
        case 'bookCModel':
	   $id = $this->fedoraObjExt->id;
            $id = explode(":",$id);
            $id = $id[1];
           $encodedUrl = $this->base_url."/uuid/".$id."?ui=embed";                
//	$encodedUrl = "https://dev.repository.ou.edu/uuid/9ab56f04-7210-5212-b3b7-c6ead8d53779?ui=embed";
            if($this->width > 0) {
                $encodedUrl .= "&wight=".$this->width;
                $this->setHeight($this->width);
                $encodedUrl .= "&height=".$this->height;
            }
            elseif($this->height > 0) {
                $encodedUrl .= "&height=".$this->height;
                $this->setWidth($this->height);
                $encodedUrl .= "&wight=".$this->width;
            }
            $resArray['type'] = "rich";
            $resArray['version'] = "1";
            $resArray['html'] = "<iframe width='".$this->iframeWidth."' height='".$this->iframeHeight."' " .
                                "src='".$encodedUrl."' frameborder='0' " .
                                //"style='-webkit-transform:scale(0.5); -moz-transform:scale(0.5); -o-transform:scale(0.5); transform:scale(0.5);' " .
                                "></iframe>";                
            break;
        default:
            echo "The islandora object model does not exist!";
            exit();
                break;
        }
        
        echo json_encode($resArray);
    }
    
    /**
     * Redirects specific requests to display of islandora content model objects
     */
    public function getEmbeddedObjUI()
    {
        $objModel = $this->fedoraObjExt->getFedoraObjectModel(); 
        switch($objModel){
        case 'bookCModel':
            $encodedUrl = $this->base_url."/islandora/object/".$this->fedoraObjExt->id;                
            if($this->width > 0) {
                $encodedUrl .= "&wight=".$this->width;
                $this->setHeight($this->width);
                $encodedUrl .= "&height=".$this->height;
            }
            elseif($this->height > 0) {
                $encodedUrl .= "&height=".$this->height;
                $this->setWidth($this->height);
                $encodedUrl .= "&wight=".$this->width;
            }
                
            drupal_goto($encodedUrl);
            break;
        default:
            echo "The islandora object model does not exist!";
            exit();
                break;
        }
    }
    
    /**
     * Generate the XML response based on Oembed requests
     */
    public function getXmlResponse()
    {
        
    }
}

