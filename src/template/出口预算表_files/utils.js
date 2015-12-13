/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <returns></returns>
function PopDialog(urls,args,width,height)
{
	showModalDialog(urls,args,'center: Yes; help: Yes; resizable: no;scroll:no;status: yes;dialogHeight:'+(parseInt(height)+20)+'px;dialogWidth:'+width+'px');
	//alert('center: Yes; help: Yes; resizable: no; status: no;scroll:no;dialogHeight:'+height+'px;dialogWidth:'+width+'px');
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <returns></returns>
function WindowOpen(urls,strName,width,height)
{
	open(urls,strName,"height="+height+",width="+width+",center=yes,toolbar=no,menubar=no,scrollbars=yes,location=no,resizable=yes,status=yes");
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <returns></returns>
function toppage()
{
	if (self.location!=top.location)
	{
		//parent.document.all(self.name).height = 0;
		parent.document.all(self.name).height = document.body.scrollHeight;
		//parent.document.all(self.name).className = "frameCssAfter";
	}
}
/// <summary>
///
/// </summary>
/// <param name="e">this ctr</param>
/// <param name="c1">color1</param>
/// <param name="c2">color2</param>
/// <returns></returns>
function trMO(e,c1,c2)
{
	var cb1;
	e.currentcolor=e.style.backgroundColor;
	cb1=e.style.bordercolor;
	e.style.backgroundColor=c1;
	e.className="overhand";
	//e.style.borderColor=c2;
} 
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <returns></returns>
function trMU(e)
{
	e.style.backgroundColor=e.currentcolor;
	//this.style.bordercolor=cb1;
}
/// <summary>
///textbox输入数字
/// </summary>
/// <param name="textstring">textbox.text</param>
/// <param name="type">0:int;1:float</param>
/// <returns></returns>
function InputFI(textstring,type)
{
	var stringTmp = textstring;
	var kk = event.keyCode;
	if (type==0)
	{
		if ((kk>=48)&&(kk<=57))
		{
			return window.event.returnValue=true;
		}			
		else
		{
			return window.event.returnValue=false;
		}
	}
	if (type==1)
	{
		if (((kk>=48)&&(kk<=57))||(kk==46)||(kk==8))
		{
			if ((kk==46)&&(stringTmp.indexOf(".")>=0))
			{
				return window.event.returnValue=false;
			}
		}			
		else
		{
			return window.event.returnValue=false;
		}
	}
}

function MO(e)
{
	if (!e)
	var e=window.event;
	var S=e.srcElement;
	while (S.tagName!="TD")
		{
			S=S.parentElement;
		}
	S.className="T";
}
function MU(e)
{
	if (!e)
	var e=window.event;
	var S=e.srcElement;
	while (S.tagName!="TD")
	{S=S.parentElement;}
	S.className="P";
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <returns></returns>
function LoadFrom(Cls1)
{
	var drp2 = document.getElementById("drpl2");
	var n = drp2.options.length-1;
	for(var i = 0;i<=n;i++)
	{
		//drp2.remove(0);
		var oChild=drp2.children(0);
		//alert(oChild.text);	
		drp2.removeChild(oChild);
	}
	if (Cls1!="")
	{
		var oXml = new ActiveXObject("MSXML2.XMLHTTP");
		var oDom = new ActiveXObject("MSXML2.DOMDocument");
		oXml.open("Get","../Teacher/LoadDrop2.aspx?zl="+Cls1, false);
		oXml.send("");
		result = oXml.responseText;
		oDom.loadXML(result);
		//alert(oDom.xml);
		items = oDom.selectNodes("//Root/Class2");
		for (var item = items.nextNode(); item; item = items.nextNode())
		{
			var cls2 = item.selectSingleNode("ClsID").text;
			var newOption = document.createElement("OPTION");
			newOption.text = cls2;
			newOption.value = cls2;
			drp2.options.add(newOption);
		}		
	}
	else
	{
		var newOption = document.createElement("OPTION");
			newOption.text = "请选择";
			newOption.value = "";
			drp2.options.add(newOption);
		alert("请选择一个操作总类别!");		
	}	
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function CheckOption(args)
{
	var es = document.all.tags("option");
	for (var i=0;i<es.length;i++)
	{
		var e=es[i];
		var j=e.text;
		if (args==j)
		{
			e.selected=true;
		}
	}
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function LetTextReadOnly()
{
	var es = document.all.tags("input");
	for (var i=0;i<es.length;i++)
	{
		var e = es[i];
		if (e.type=="text")
		{
			e.readOnly=true;
		}
	}
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function LetTextareaReadOnly()
{
	var et = document.all.tags("TEXTAREA");
	for (var j=0;j<et.length;j++)
	{
		var ee = et[j];
			ee.readOnly=true;
	}
	//document.all["sel"].disabled = true;
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function SetXsltReadonly(style,flag)
{
	if (flag=="1")
	{			
		style.XMLDocument.selectSingleNode("//xsl:stylesheet/xsl:variable").attributes.getNamedItem("select").text="'true'";
    }
}
/*function CheckNullNode(argSource,arg1)
{
	alert(argSource.xml);
	var Node=arg1;
	var childnode1=argSource.XMLDocument.selectSingleNode(Node);
	items = childnode1.selectNodes(childnode1);
	var childnode2;
	for (var item = items.nextNode(); item; item = items.nextNode())
	{
		item.Text = "&nbsp;";
	}
	alert(source.Xml);
}*/
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function transform(target,source,style)
{
	target.innerHTML = source.transformNode(style.XMLDocument);
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function AppendNode(arg)
{
	alert(arg);
	var root;
	var Node=arg;
	var childnode1=source.XMLDocument.selectSingleNode(Node);
	root = source.XMLDocument.documentElement;
	var childnode2=sourceChild.XMLDocument.selectSingleNode(Node).cloneNode(true);
	root.appendChild(childnode2);
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function AppendNodes(arg1,arg2)
{
	var root;
	var Node=arg1;
	var ChildNode=arg2;
	var childnode1=source.XMLDocument.selectSingleNode(Node);
	root = source.XMLDocument.documentElement;
	items = sourceChild.selectNodes(ChildNode);
	var childnode2;
	for (var item = items.nextNode(); item; item = items.nextNode())
	{
		childnode2=item.cloneNode(true)
		root.appendChild(childnode2);
	}	
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function RemoveNodes(arg1,arg2)
{
	var root;
	var Node=arg1;
	var ChildNode=arg2;	
	root = source.XMLDocument.documentElement;
	items = source.selectNodes(ChildNode);
	/*for (var item = items.nextNode(); item; item = items.nextNode())//第一种去除方法
	{
		root.removeChild(item);
	}*/
	while (items.peekNode() != null) //第二种去除方法
	{
		items.removeNext();
	}

}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function doClientSubmit(arg1,arg2,arg3,args4,arg5)
{
	var result="";
	var oXml = new ActiveXObject("MSXML2.XMLHTTP");
	var oDom = new ActiveXObject("MSXML2.DOMDocument");
	oXml.open(arg1,arg2,arg3);
	oXml.send(args4);
	if (arg5=="text")
	{
		result = oXml.responseText;
	}
	else if (arg5=="xml")
	{
		result = oXml.responseXML;
	}	
	return result;
}
/// <summary>
/// 返回信息页面的字符串
/// </summary>
/// <param name="strMode">提示信息的模式:Manager;Cast</param>
/// <param name="strUrl">提示信息的URL路径</param>
/// <param name="strMsgID">提示信息的ID</param>
/// <param name="strMsg">提示信息</param>
/// <param name="strCloseID">关闭窗口的模式:Refrush;Close</param>
/// <param name="strBtnMode">窗口BUTTON模式:Close;Back</param>
/// <returns>构造后字符串</returns>
function ShowMessage(strMode,strUrl,strMsgID,strMsg,strCloseID,strBtnMode)
{
	var str;
	var msg=strMsg;
	if (strMsgID == "-1")
	{
		strMsgID = "1";
	}
	if (strMode=="Manager")
	{	
		str=strUrl+"?errmode="+strMode+"&errid="+strMsgID+"&errCloseID="+strCloseID+"&errBtnMode="+strBtnMode+"&errmsg="+msg;
		//str=strUrl+"?errmode="+strMode+"&errid="+strMsgID;
		PopDialog(str,window,'493','337');		
	}
	else
	{
		str="\""+strUrl+"?errmode="+strMode+"&errid="+strMsgID+"&errmsg="+msg;
		PopDialog(str,window,'493','337');	
	}
	//return str;
}
/// <summary>
/// 改变对象的CSS
/// </summary>
/// <param name="e">改变的目标对象</param>
/// <param name="strCss">改变的CSS名</param>
/// <returns>构造后字符串</returns>
function ChangeCss(e,strCss)
{
	e.className = strCss;
}
//---------------------------------------------------------------------------------------------------//
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function HideTd(e,oper)
	{
		var tmp1="";
			tmp1="td"+e;			
		var tmp2=e-1;
			tmp2="td"+tmp2;
		var tmp3=e-1;
			tmp3="Tbl"+tmp3;
		if (oper==0)
		{
			Htd(tmp1,tmp2,tmp3,e);
		}
		if (oper==1)
		{		
			var tmpFlag = document.all["flag1"].value;
			if ((tmpFlag!="")&&(tmpFlag!=e))		
			{
				var J1="td"+tmpFlag;
				var J2=parseInt(tmpFlag,10)-1
					J2="td"+J2;
				var J3=parseInt(tmpFlag,10)-1
					J3="Tbl"+J3;
				Htd(J1,J2,J3,tmpFlag);
			}
			Otd(tmp1,tmp2,tmp3,e);
			document.all["flag1"].value=e;		
		}
	}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function Htd(args1,args2,args3,args4)
{
	document.all[args1].style.display="none";
	document.all[args3].className = "frameTable0";
	document.all[args2].innerHTML="<img name='a"+args4+"' id='a"+args4+"' border=0 src='images/console/xiangxia.gif' onclick='javascript:HideTd("+args4+",1)'>";
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function Otd(args1,args2,args3,args4)
{
	var tmpDir="childFrm"+args4;
	document.all[args1].style.display="inline";
	document.all[args3].className = "frameTable1";
	document.all[args2].innerHTML="<img name='a"+args4+"' id='a"+args4+"' border=0 src='images/console/xiangshang.GIF' onclick='javascript:HideTd("+args4+",0)'>";
	var tmpID = "";
	if (document.all["flag3"] != undefined)
	{
		tmpID = document.all["flag3"].value;
		tmpID = "?id="+tmpID;
	}
	switch (args4)
	{
		case 2:window.frames[tmpDir].location=document.all["url1"].value+tmpID;break;
		case 4:window.frames[tmpDir].location=document.all["url2"].value+tmpID;break;
	}
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function Otr(e,args1,args2)
{
	e.className="overhand";
	if (args2==0)
	{
		document.all[args1].className = "frameTable1";
	}
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function Utr(args1,args2)
{
	if (args2==0)
	{
			document.all[args1].className = "frameTable0";			
	}
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function MM_preloadImages() 
{ //v3.0
	var d=document; 
	if	(d.images)
		{
		if(!d.MM_p) d.MM_p=new Array();
		var i,j=d.MM_p.length,a=MM_preloadImages.arguments; 
		for(i=0; i<a.length; i++)
			{
			if (a[i].indexOf("#")!=0)
				{ 
				d.MM_p[j]=new Image; 
				d.MM_p[j++].src=a[i];
				}
			}
		}
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function SetFrame(strCls)
{
	//var tmpID = "";
		//tmpID = document.all["flag3"].value;
		//tmpID = "?id="+tmpID;
	if (strCls == "1")
	{
		document.all["childFrm4"].src = document.all["url1"].value;
	}
	else if (strCls != "1")//不是出口商	{
		if (strCls == "2")//进口商		{
			document.all["childFrm4"].src = document.all["url1"].value;
		}
		if (strCls == "3")//工厂
		{
			document.all["childFrm4"].src = document.all["url2"].value;
		}
		if (strCls == "4")//出口地银行
		{
			document.all["childFrm4"].src = document.all["url2"].value ;
		}
		if (strCls == "5")//进口地银行
		{
			document.all["childFrm4"].src = document.all["url2"].value ;
		}
	}	
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function setHeight()
{
	alert(e1.height+"\n"+e2.height);		
	if (e1.height<e2.height)
	{
		e2.height = e1.height;
	}
}
//---------------------------------------------------------------------------------------------------//
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function ChangeFrame(op,strPaths)
{
	op.src = strPaths;
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function chk()
{
	var es = document.all.tags("input");
	var k=0;
	for (var i=0;i<es.length;i++)
	{
		var e = es[i];
		if (e.type=="radio" && e.name=="mark")
		{	
			k++;
			if (e.checked)
			{
				document.all["flag"].value=e.value;
				break;
			}
		}
	}
	if (k=0) {document.all["flag"].value=""}
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function GetID()
{
	document.all["flag"].value = "";
	var es = document.getElementsByName("mark")
	for (var i =0;i<es.length;i++)
	{
		var e = es[i];
		if (e.checked)
		{
			document.all["flag"].value = document.all["flag"].value + e.value + ";";
		}
	}
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function GetOrder()
{
	var id = parent.window.frames["childFrm"].document.all["txtM0701"].innerText;
	document.all["flag1"].value = id;
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function SetID(strID)
{
	parent.window.document.all["cid"].value = strID;
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function Go2Url(obj1,obj2,strAspx,iOp,strKey,strPass)
{
	var k="";
	var j="";
		//j = document.all["arg"].value;
	if (obj2.document.all[strKey] != undefined)
	{
		k = obj2.document.all[strKey].innerText;
	}
	if (k!="")
	{
		/*if (strPass != "1")
		{*/
			if (iOp == 0)
			{
				//strAspx = strAspx + "?mod="+j+"&id=" + k;
				strAspx = strAspx + "?id=" + k;
			}
			else if (iOp == 1)
			{
				//strAspx = strAspx + "&mod="+j+"&id=" + k;
				strAspx = strAspx + "&id=" + k;
			}
		/*}
		else if (iOp == 1)
		{
			alert("你确定对合同"+k+"进行操作?");
			return false;
		}*/
	}
	else if (strPass == "1")
	{
		alert("请先设置主合同!");
		if (obj1.location != document.all["btnCheck"].href) obj1.location = document.all["btnCheck"].href;		
		return false;
	}
	obj1.location = strAspx;
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
function goBack(strUrl)
{
	window.location.replace(strUrl);
}
/// <summary>
///
/// </summary>
/// <param name=""></param>
/// <returns></returns>
function SetVisiable(obj1,obj2,obj3,flag)
{
	//alert(obj1+"\n"+obj2+"\n"+obj3+"\n"+flag);
	if (flag == 1)//unvisiable
	{
		obj1.style.cosplan = 3;
		obj1.style.width = 367;
		obj2.style.display = "none";
		obj3.style.display = "none";
	}
	else
	{
		obj1.style.width = 140;
		obj2.style.display = "inline";
		obj3.style.display = "inline";
		obj2.style.width = 87;
		obj3.style.width = 140;
	}
}
function Parent2Back()
{
	var k = "";
	if (parent.window.document.all["arg"] != undefined)
	{
		k = parent.window.document.all["arg"].value;
		window.location.replace("../common/DefaultInfo.aspx?id="+k);
	}
}
function ParentChildRefrush(obj,arg)
{
	var tmpUrl = obj.frames[arg].location;
	obj.frames[arg].location = tmpUrl;
}
/******************************************************/
        function CheckIt(op,cls)
        {
			var flag = document.all["flag"].value;
			if (flag !="0")//非只读
			{
        		var tmpValue = "";
				tmpValue = GetCls(cls);
				var kk = op.name + "h";
        		if (op.value == "")
        		{
					op.readOnly = false;
					op.value = tmpValue;
					document.all[kk].value="1";
					op.readOnly = true;	
				}
				else if (op.value == tmpValue)
				{
					op.readOnly = false;
					op.value = "";
					document.all[kk].value="0";
					op.readOnly = true;	
				}
			}
			else//只读
			{
				return false;
			}
        }
        function GetCls(pk)
        {
			var strReturn = "";
			switch (pk)
			{
				case 0:strReturn = "√";break;
				case 1:strReturn = "×";break;
				case 2:strReturn = "××";break;
			}
			return strReturn;
        }
        function LoadCheckBox(op,cls)
        {
			var tmpValue = "";
				tmpValue = GetCls(cls);			
			if (op.value=="1")
			{
				var k = op.name.substring(0,op.name.length-1);
				document.all[k].readOnly=false;
				document.all[k].value=tmpValue;
				document.all[k].readOnly=true;
			}
        }        
        
        
function InputUserID()
{
	var kk = event.keyCode;
	if ((kk>=48)&&(kk<=57)||((kk>=65)&&(kk<=90))||((kk>=97)&&(kk<=122))||(kk==95))
	{
		return window.event.returnValue=true;
	}
	else
	{
		return window.event.returnValue=false;
	}
}
/******************************************************/