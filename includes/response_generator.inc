<?php

Class FedoraObjectExtended extends FedoraObject
{
    public function __construct($id, $repository){
        parent::__construct($id, $repository);
    }
    
    //"info:fedora/islandora:bookCModel"
    public function getFedoraObjectModel(){
        $profile = $this->getFedoraObjectProfile();
        $model_arr = explode(':',$profile['objModels'][0]);
        $size = count($model_arr);
        return $model_arr[$size-1];
    }

    public function getFedoraObjectProfile() {
        return $this->objectProfile;
    }

}

Class RespsonseGenerator
{
    protected $fedoraObjExt;
    protected $iframeHeight;
    protected $iframeWidth;
    protected $height;
    protected $width;


    public function __construct(FedoraObjectExtended $fedoraObjExt, $base_url, $height = 500, $width = 500, $iframeHeight = 500, $iframeWidth = 500){
        
        if($height != 500)
            $iframeHeight = $height;
        if($width != 500)
            $iframeWidth = $width;
        
        $this->fedoraObjExt = $fedoraObjExt;
        $this->height = $height;
        $this->width = $width;
        $this->iframeHeight = $iframeHeight;
        $this->iframeWidth = $iframeWidth;
        $this->base_url = $base_url;
    }
    
    public function setIframeHeight($iframeHeight){
        $this->iframeHeight = $iframeHeight;
    }
    
    public function setIframeWidth($iframeWidth){
        $this->iframeWidth = $iframeWidth;
    }
    
    public function setHeight($height){
        $this->height = $height;
    }
    
    public function setWidth($width){
        $this->width = $width;
    }
    
    public function getJSONResponse(){
        
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
                $encodedUrl = $this->base_url."/islandora/object/".$this->fedoraObjExt->id."?ui=embed";                
                if($this->width > 0){
                    $encodedUrl .= "&wight=".$this->width;
                    $this->setHeight($this->width);
                    $encodedUrl .= "&height=".$this->height;
                }
                elseif($this->height > 0){
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
    
    public function getEmbeddedObjUI(){
        $objModel = $this->fedoraObjExt->getFedoraObjectModel(); 
        switch($objModel){
            case 'bookCModel':
                $encodedUrl = $this->base_url."/islandora/object/".$this->fedoraObjExt->id;                
                if($this->width > 0){
                    $encodedUrl .= "&wight=".$this->width;
                    $this->setHeight($this->width);
                    $encodedUrl .= "&height=".$this->height;
                }
                elseif($this->height > 0){
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
    
    public function getXmlResponse(){
        
    }
}
