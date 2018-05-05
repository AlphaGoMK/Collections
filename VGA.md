# VGA  
### Instance-aware Image and Sentence Matching with Selective Multimodal LSTM

* Motivation:  
  1. instance aware matching not only using global similarity  
  2. only partial salient instance pairs describing the same semantic concept can actually be associated and contribute to the global similarity  
  
* Model:
  1. extracts their instance candidates.  
  2. exploit context attention scheme to selectively attend to instance pairs.
    * saliency maps
    * combine saliency weighted representations
    * global context as reference
