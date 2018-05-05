# Weakly supervised object localization
### Weakly Supervised Object Localization Using Things and Stuff Transfer
* Motivation
  1. exploit source-target similarity and source-target against background
  
* Method
  1. segmentation model, similarity relation between targe and source, cooccurrence relation between thing and stuff class.
  2. class similarity and co-occurrence map to refine stuff segmentation map
  3. make maps as cues to multiple instance learning, transferred knowledge from pixel to object proposal.
