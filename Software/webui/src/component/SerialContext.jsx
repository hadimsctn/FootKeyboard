import React, { createContext, useRef, useState } from "react";

export const SerialContext = createContext();

export const SerialProvider = ({ children }) => {
    const [port, setPort] = useState(null);
    const [output, setOutput] = useState("");
    const [receivedData, setReceivedData] = useState(""); // Dữ liệu nhận được từ Serial
    const portRef=useRef(null);
  const connectToSerial = async (nameDevice,delayKey,button1,button2,button3,button4) => {
    if ("serial" in navigator) {
      try {
        const selectedPort = await navigator.serial.requestPort();
        await selectedPort.open({ baudRate: 115200 });
        portRef.current=selectedPort;
        alert("Connected to Foot Keyboard");
        // Gửi tin nhắn ngay khi kết nối thành công
        await sendData(nameDevice,delayKey,button1,button2,button3,button4,selectedPort);

        // Đọc dữ liệu phản hồi sau khi gửi tin nhắn
        await readData(selectedPort);
      } catch (error) {
        console.error("Error connecting to serial port:", error);
        alert("Failed to connect to serial port.");
      }
    } else {
      setOutput("Web Serial API is not supported in your browser.");
    }
  };
  const sendData = async (nameDevice,delayKey,button1,button2,button3,button4,port) => {
    if (true) {
      if (!port.readable || !port.writable) {
        try {
          await port.open({ baudRate: 115200 });
        } catch (err) {
          console.error("Failed to open port:", err);
          return;
        }
      }
      const encoder = new TextEncoderStream();
      const writableStreamClosed = encoder.readable.pipeTo(port.writable);
      const writer = encoder.writable.getWriter();
      if(delayKey!=""){
        await writer.write("TK="+delayKey+"\n");
      }
      if(button1!=""){
        await writer.write("01="+button1+"\n");
      }
      
      if(button2!=""){
        await writer.write("02="+button2+"\n");
      }
      
      if(button3!=""){
        await writer.write("03="+button3+"\n");
      }
      
      if(button4!=""){
        await writer.write("04="+button4+"\n");
      }
      if(nameDevice!=""){
        await writer.write("NAME="+nameDevice);
      }      
      writer.close();
    } else {
      console.error("No serial connection available.");
    }
  };

  const readData = async (port) => {
    if (port) {
      const decoder = new TextDecoderStream();
      const readableStreamClosed = port.readable.pipeTo(decoder.writable);
      const reader = decoder.readable.getReader();
      let data="";
      try {
        const { value, done } = await reader.read();
        data+=value;  
        alert("Cập nhật nút bấm thành công, F5 để tiếp tục");
        
         // Lưu dữ liệu nhận được
      } catch (error) {
        console.error("Error reading from serial port:", error);
      } finally {
        reader.releaseLock();
      }
    } else {
      console.error("No serial connection available.");
    }
  };
  
  return (
    <SerialContext.Provider
      value={{
        connectToSerial,
        sendData,
        receivedData,
        output,
        port, 
        setPort,
      }}
    >
      {children}
    </SerialContext.Provider>
  );
};
