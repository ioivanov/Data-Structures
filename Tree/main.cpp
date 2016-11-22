Tree<int> t1(1);
t1.addChild(TestTree(2)
				.addChild(TestTree(3))
				.addChild(TestTree(4)
						  .addChild(TestTree(5))
						  .addChild(TestTree(6)))
			    .addChild(TestTree(7))
			    .addChild(TestTree(8)))
	  .addChild(TestTree(9))
.addChild(TestTree(10));
