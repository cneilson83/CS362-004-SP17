/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator validator = new UrlValidator();
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       //These should all return true
	   if (!urlVal.isValid("http://www.amazon.com")) {
	       System.out.println("http://www.amazon.com - Error expected true");
       }
       if (!urlVal.isValid("http://amazon.com")) {
           System.out.println("http://amazon.com - Error expected true");
       }
       if (!urlVal.isValid("http://amazon.com/shouldpass")) {
           System.out.println("http://amazon.com/shouldpass - Error expected true");
       }
       if (!urlVal.isValid("http://amazon.com/should/pass")) {
           System.out.println("http://amazon.com/should/pass - Error expected true");
       }
       if (!urlVal.isValid("http://255.255.255.255")) {
           System.out.println("http://255.255.255.255 - Error expected true");
       }


       //These should all return false
       if (urlVal.isValid("://www.amazon.com")) {
           System.out.println("://www.amazon.com -  Error expected false");
       }
       if (urlVal.isValid("http:/www.amazon.com")) {
           System.out.println("http:/www.amazon.com - Error expected false");
       }
       if (urlVal.isValid("http://www.amazon")) {
           System.out.println("http://www.amazon - Error expected false");
       }
       if (urlVal.isValid("abc://www.amazon.com")) {
           System.out.println("abc://www.amazon.com - Error expected false"); //BUG returns true despite invalid URL Scheme
       }
       if (urlVal.isValid("http//www.amazon.com")) {
           System.out.println("http//www.amazon.com - Error expected false");
       }
       if (urlVal.isValid("")) {
           System.out.println("Empty url - Error expected false");
       }
       if (urlVal.isValid("ajka;kjnsg;kjna")) {
           System.out.println("ajka;kjnsg;kjna - Error expected false");
       }
       if (urlVal.isValid("http://666.666.666.666")) {
           System.out.println("http://666.666.666.666 - Error expected false"); //BUG returns true, but address is too large
       }
	   
   }
   
   
   public void testSchemePartition()
   {
	   //scheme partition
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	 
	   //first 3 are true
	   String scheme[] = {"http://", "ftp://", "h3t://", "3ht://", "http:/", "http:", "http/", "://", "abcd"};
	   
	   for(int i = 0; i < scheme.length; i++){
		   String url = scheme[i] + "www.amazon.com";
		   if(i > 2){
			   if(urlVal.isValid(url) != false){
				   System.out.println(url + " - Error expected false");
			   }
		   }
		   else{
			   if(urlVal.isValid(url) != true){
				   System.out.println(url + " - Error expected true");
			   }
		   }
	   }  
   }
   
   public void testAuthorityPartition()
   {
       UrlValidator validator = new UrlValidator();
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       String authorityTrue[] = {"www.amazon.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com", "go.cc"};
       String authorityFalse[] = {"256.256.256.256", "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4", "go.a", "go.a1a", "go.1aa", "aaa.", ".aaa", "aaa", ""};
       String url;
       boolean expected = true;

       for (int i = 0; i < authorityTrue.length; i++) {
           url = "http://";
           url = url + authorityTrue[i];
           if (urlVal.isValid(url) != expected){
               System.out.println(url + " - Error expected true");
           }
       }

       expected = false;
       for (int i = 0; i < authorityFalse.length; i++) {
           url = "http://";
           url = url + authorityFalse[i];
           if (urlVal.isValid(url) != expected){
               System.out.println(url + " - Error expected false");
           }
       }

   }

   public void testPortPartition()
   {
       UrlValidator validator = new UrlValidator();
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       String portTrue[] = {":80", ":65535", ":0", "", ":65636"};
       String portFalse[] = {":-1", ":65a"};
       String url;
       boolean expected = true;

       for (int i = 0; i < portTrue.length; i++) {
           url = "http://www.amazon.com";
           url = url + portTrue[i];
           if (urlVal.isValid(url) != expected){
               System.out.println(url + " - Error expected true");
           }
       }

       expected = false;
       for (int i = 0; i < portFalse.length; i++) {
           url = "http://www.amazon.com";
           url = url + portFalse[i];
           if (urlVal.isValid(url) != expected){
               System.out.println(url + " - Error expected false");
           }
       }
   }
   
   
   public void testPathPartition()
   {
       UrlValidator validator = new UrlValidator();
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       String pathTrue[] = {"/test1", "/t123", "/$23", "/test1/", "", "/test1/file"};
       String pathFalse[] = {"/..", "/../", "/..//file", "/test1//file"};
       String url;
       boolean expected = true;

       for (int i = 0; i < pathTrue.length; i++) {
           url = "http://www.amazon.com:0";
           url = url + pathTrue[i];
           if (urlVal.isValid(url) != expected){
               System.out.println(url + " - Error expected true");
           }
       }

       expected = false;
       for (int i = 0; i < pathFalse.length; i++) {
           url = "http://www.amazon.com:0";
           url = url + pathFalse[i];
           if (urlVal.isValid(url) != expected){
               System.out.println(url + " - Error expected false");
           }
       }
   }

   public void testQueryPartition()
   {
       UrlValidator validator = new UrlValidator();
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       String queryTrue[] = {"?action=view", "?action=edit&mode=up"};
       String queryFalse[] = {"asdlkfjasklj", "1829487naskjasl.asdf..as"};
       String url;
       boolean expected = true;

       for (int i = 0; i < queryTrue.length; i++) {
           url = "http://www.amazon.com:80";
           url = url + queryTrue[i];
           if (urlVal.isValid(url) != expected){
               System.out.println(url + " - Error expected true");
           }
       }

       expected = false;
       for (int i = 0; i < queryFalse.length; i++) {
           url = "http://www.amazon.com:80";
           url = url + queryFalse[i];
           if (urlVal.isValid(url) != expected){
               System.out.println(url + " - Error expected false");
           }
       }
   }

    public void testIsValid() {
        //first 3 are true
        String scheme[] = {"http://", "ftp://", "h3t://", "3ht://", "http:/", "http:", "http/", "://"};

        //first 7 are true
        String authority[] = {"www.amazon.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com", "go.cc", "256.256.256.256", "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4", "go.a", "go.a1a", "go.1aa", "aaa.", ".aaa", "aaa", ""};

        //first 5 are true
        String port[] = {":80", ":65535", ":0", "", ":65636", ":-1", ":65a"};
        
        //first 6 are true
        String path[] = {"/test1", "/t123", "/$23", "/test1/", "", "/test1/file", "/..", "/../", "/..//file", "/test1//file"};

        //all true
        String query[] = {"?action=view", "?action=edit&mode=up"};

        //int[] index = {0,0,0,0};
        String url = "";
        boolean expected, result;

        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        for (int i = 0; i < scheme.length; i++) {
            for (int j = 0; j < authority.length; j++) {
                for (int k = 0; k < port.length; k++) {
                    for (int m = 0; m < path.length; m++) {
                        for (int n = 0; n < query.length; n++) {
                            expected = true;
                            if (i > 2 || j > 6 || k > 4 || m > 5) {
                                expected = false;
                            }
                            url = scheme[i] + authority[j] + port[k] + path[m] + query[n];
                            if (urlVal.isValid(url) != expected) {
                                System.out.println(url);
                            }
                        }
                    }
                }
            }
        }
    }
   
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
}
