## Rules Comparison

We examined the differences between our approach and four SOTA methods in terms of three aspects: the adversarial example generation techniques, the inclusion of interpretability analysis, and the initial attack target. The analysis results are summarized in Table \ref{Table 8}. 

Firstly, in terms of adversarial example generation techniques, the MHM and ALERT methods generate adversarial examples solely through identifier renaming. The CARROT method extends this by incorporating method renaming and code statement optimization, while CODA further refines this by adding replacements for loops, conditional statements, and constants. In comparison to these methods, our approach considers a broader range of code synonymous transformation techniques when generating adversarial examples, such as code execution order, junk code insertion, and statement redefinition, among others. 

Secondly, none of the MHM, ALERT, CARROT, or CODA methods analyze the reasons behind the successful attack of their generated adversarial examples on the target models, nor do they perform fine-grained interpretability analysis. In contrast, our approach analyzes whether there are differences in the top 15 most important features of the vulnerability models' attention, both for the original and adversarial examples. These differences may serve as the underlying reasons for the success of the attack. 

Lastly, the attack targets of these methods are primarily the deep learning models themselves, rather than deep vulnerability detection methods. Our approach takes into account abstract code structures commonly used in the preprocessing phase of vulnerability detection methods, which are often provided as input to deep learning models. Alterations to these abstract code structures contribute to the model's mispredictions.



## Usability Analysis

In real-world scenarios, engineers deploy deep vulnerability detection models to conduct code auditing for developed software products. If a malicious developer has deliberately written vulnerability backdoor code and uses code synonym transformation techniques to evade the inspection of deep vulnerability detection models, successful circumvention could pose significant security risks to enterprises. Meanwhile, during the update and iteration process of open-source software, the git push command is often used to request merging patch code into the main branch of the repository. Some malicious developers or testers may also use synonymous transformation to make vulnerable code evade the detection of the model. Additionally, name obfuscation in code obfuscation is commonly employed to fortify software products and prevent reverse engineering. However, it also undermines the detection capabilities of existing models to a certain extent, thereby enabling some vulnerabilities to successfully evade detection. Our research can effectively mitigate various issues induced by such scenarios.
