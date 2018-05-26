# VQA  
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
  
### Hierarchical Question-Image Co-Attention for Visual Question Answering

* Motivation:
  1. introduce question attention
  2. hierarchical reasoning
* Model:  
  1. Word-level feature -- CNN max-pooling \(uni/bi/trigram\) -- \> phrase level -- LSTM encoding -- \> question level
  2. Co-Attention Parallel:
    * connect image-question pair's feature similarity = \> affinity matrix
    * affinity as feature to predict attention maps
  3. Co-Attention Alternating:
    * question to vec
    * question summary attention on image feature repre.
    * image feature attention on question repre.
    
  4. Encode recursively using MLP, predict from 3 level.
